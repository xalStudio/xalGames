#include "Room.hpp"
#include <network/Server.hpp>

#include <game/phase/Game.hpp>
#include <game/phase/Lobby.hpp>

#include <chrono>
#include <iostream>

using json = nlohmann::json;

namespace xal { namespace game { namespace session {
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

        const std::filesystem::path lobbyLuaFilePath = serverDirPath / phase::Lobby::LUA_FILE;
        const std::filesystem::path gameLuaFilePath  = serverDirPath / phase::Game::LUA_FILE;

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

        if (!std::filesystem::exists(lobbyLuaFilePath)) {
            throw std::filesystem::filesystem_error(
                "[Room]The server lobby lua file doesn't exists\n",
                lobbyLuaFilePath, 
                std::error_code()
            );
        }

        if (!std::filesystem::exists(gameLuaFilePath)) {
            throw std::filesystem::filesystem_error(
                "[Room]The server game lua file doesn't exists\n",
                gameLuaFilePath, 
                std::error_code()
            );
        }
    }

    void Room::run() {
        // m_gamePhase = std::make_unique<phase::Lobby>(std::filesystem::path(m_gameDir / GAME__SERVER_DIR_PATH / phase::Lobby::LUA_FILE));

        auto m_currentTime = std::chrono::system_clock::now();

        while (true) {
            const auto timeNow = std::chrono::system_clock::now();
            double frameTime = std::chrono::duration<double>(timeNow - m_currentTime).count();
            m_currentTime = timeNow;

            if (frameTime > 0.25) {
                std::cout << "Sleep for " << frameTime - 0.25f << "\n";
                std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - 0.25f));
                frameTime = 0.25;
            }

            m_accumulator += frameTime;

            std::cout << "m_accumulator: " << m_accumulator << "\n";

            bool oneQueueEmpty = false;
            while (m_accumulator >= m_TPS) {
                json message;

                {
                    const std::lock_guard<std::mutex> lock(getMutex(m_currentQueue));

                    auto& queue = getMessagesQueue(!m_currentQueue);

                    if (queue.size() == 0) {
                        if (oneQueueEmpty) break;

                        m_currentQueue.store(!m_currentQueue);
                        oneQueueEmpty = true;

                        m_accumulator -= m_TPS;
                        continue;
                    }

                    message = queue.front();
                    queue.pop();
                }

                m_accumulator -= m_TPS;
            }
        }
    }
    
    void Room::onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const json& message) {
        const std::lock_guard<std::mutex> lock(getMutex(!m_currentQueue));

        getMessagesQueue(!m_currentQueue).push(message);
    }

    std::mutex& Room::getMutex(bool getA) {
        return getA ? m_mutexA : m_mutexB;
    }

    Room::MessagesQueue& Room::getMessagesQueue(bool getA) {
        return getA ? m_messagesQueueA : m_messagesQueueB;
    }
} } }