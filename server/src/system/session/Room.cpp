#include "Room.hpp"
#include <network/Server.hpp>

// #include <system/phase/Game.hpp>
#include <system/phase/lobby/LuaLobby.hpp>

#include <chrono>
#include <iostream>

using json = nlohmann::json;

namespace xal { namespace system { namespace session {
    const std::string Room::ARG__GAME_DIR = "--game-dir";
    const std::string Room::GAME__SERVER_DIR_PATH = "server";
    const std::string Room::GAME__CLIENT_DIR_PATH = "client";

    void Room::setGame(const std::string_view gameDir) {
        std::cout << "[Room]Loading game from \"" << gameDir << "\"\n"; 

        m_gameDir = std::filesystem::path(gameDir);

        if (!std::filesystem::exists(m_gameDir)) {
            std::cerr << "[Room]The directory \"" << gameDir << "\" doesn't exists\n";
        }

        const std::filesystem::path serverDirPath = m_gameDir / GAME__SERVER_DIR_PATH;
        const std::filesystem::path clientDirPath = m_gameDir / GAME__CLIENT_DIR_PATH;

        // const std::filesystem::path lobbyLuaFilePath = serverDirPath / phase::Lobby::LUA_FILE;
        // const std::filesystem::path gameLuaFilePath  = serverDirPath / phase::Game::LUA_FILE;

        if (!std::filesystem::exists(serverDirPath)) {
            throw std::filesystem::filesystem_error(
                "[Room]The server directory doesn't exists\n", 
                serverDirPath, 
                std::error_code()
            );
        }

        if (!std::filesystem::exists(clientDirPath)) {
            throw std::filesystem::filesystem_error(
                "[Room]The client directory doesn't exists\n", 
                clientDirPath, 
                std::error_code()
            );
        }

        // if (!std::filesystem::exists(lobbyLuaFilePath)) {
        //     throw std::filesystem::filesystem_error(
        //         "[Room]The server lobby lua file doesn't exists\n",
        //         lobbyLuaFilePath, 
        //         std::error_code()
        //     );
        // }

        // if (!std::filesystem::exists(gameLuaFilePath)) {
        //     throw std::filesystem::filesystem_error(
        //         "[Room]The server game lua file doesn't exists\n",
        //         gameLuaFilePath, 
        //         std::error_code()
        //     );
        // }
    }

    void Room::run() {
        m_gamePhase = std::make_unique<phase::LuaLobby>(m_gameDir / GAME__SERVER_DIR_PATH / phase::LuaLobby::LUA_FILE);

        m_gamePhase->run(this);
    }
    
    void Room::onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const json& message) {
        // m_messagesQueuePtr->onMessage(server, hdl, message);
    }
} } }