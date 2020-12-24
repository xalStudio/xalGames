#include <memory>
#include <functional>
#include <iostream>
#include <thread>

#include "network/Server.hpp"
#include "system/session/Room.hpp"
#include "system/session/RoomPool.hpp"
#include "utils/CmdArguments.hpp"

static const std::string ARG__ONLY_LOBBY = "--only-lobby";

using namespace xal;

int main(int argc, char** argv) {
    utils::CmdArguments arguments(argc, argv);

    uint port;
    if (!arguments.has(network::Server::ARG__PORT)) {
        std::cerr << "Missing \"--port\" argument\n";
        return 1;
    } else {
        port = std::stoi(std::string(arguments.get(network::Server::ARG__PORT)));
    }

    network::Server server;

    server.initialize(port);

    if (arguments.has(ARG__ONLY_LOBBY)) {
        if (!arguments.has(system::session::Room::ARG__GAME_DIR)) {
            std::cerr << "Missing \"--game-dir\" argument\n";
            return 1;
        }

        system::session::Room room;
        room.setGame(arguments.get(system::session::Room::ARG__GAME_DIR));
        
        using namespace std::placeholders;
        server.addMessagesHandler("", std::bind(&system::session::Room::onMessage, &room, _1, _2, _3));

        std::thread t(std::bind(&system::session::Room::run, &room));

        server.run();
        t.join();
    } else {
        // system::session::RoomPool roomPool;
    }

    return 0;
}