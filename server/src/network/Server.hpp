#pragma once

#define ASIO_STANDALONE

#include <asio/io_context.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "WebsocketServer.hpp"

namespace xal { namespace network {
    class Server {
    public:
        typedef std::function<void(WebsocketServer*, websocketpp::connection_hdl, const nlohmann::json&)> MessagesHandler;

        static const std::string ARG__PORT;

    public:
        Server();

        void initialize(uint port);
        int  run();

        void addMessagesHandler(const std::string& key, MessagesHandler handler);

    private:
        void onMessage(websocketpp::connection_hdl hdl, WebsocketServer::message_ptr msg);

    private:
        WebsocketServer  m_server;
        asio::io_context m_io_context;
        uint             m_port;

        std::unordered_map<std::string, MessagesHandler> m_messagesHandlers;
    };
} }