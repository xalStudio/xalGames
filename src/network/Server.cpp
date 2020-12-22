#include "Server.hpp"

#include <websocketpp/config/asio_no_tls.hpp>
#include <iostream>
#include <functional>

namespace xal { namespace network {
    const std::string Server::ARG__PORT = "--port";

    Server::Server() {
        
    }

    void Server::initialize(uint port) {
        // try {
        //     if (argc > 1 && std::string(argv[1]) == "-d") {
        //         m_server.set_access_channels(websocketpp::log::alevel::all);
        //         m_server.set_error_channels(websocketpp::log::elevel::all);
        //     } else {
        //         m_server.set_access_channels(websocketpp::log::alevel::none);
        //         m_server.set_error_channels(websocketpp::log::elevel::none);
        //     }
        // } catch (websocketpp::exception const & e) {

        // }

        m_port = port;

        m_server.init_asio(&m_io_context);
        m_server.listen(port);

        using namespace std::placeholders;
        m_server.set_message_handler(std::bind(&Server::onMessage, this, _1, _2));
    }

    int Server::run() {
        std::cout << "[Server]Starting server on " << m_port << "\n";

        m_server.start_accept();
        m_server.run();

        return 1;
    }

    void Server::addMessagesHandler(const std::string& key, MessagesHandler handler) {
        m_messagesHandlers.emplace(key, handler);
    }

    void Server::onMessage(websocketpp::connection_hdl clientHandler, WebsocketServer::message_ptr messageRaw) {
        std::cout << "on_message called with hdl: " << clientHandler.lock().get()
              << " and message: " << messageRaw->get_payload()
              << std::endl;

        using json = nlohmann::json;
        json message;

        try {
            message = json::parse(messageRaw->get_payload());
        } catch (json::parse_error& ex) {
            std::cerr << "parse error at byte " << ex.byte << "\n";
        }

        for (auto it = m_messagesHandlers.begin(); it != m_messagesHandlers.end(); ++it) {
            it->second(&m_server, clientHandler, message);
        }
    }
} }