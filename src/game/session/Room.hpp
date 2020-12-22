#pragma once

#include <string_view>
#include <string>
#include <memory>
#include <filesystem>
#include <queue>
#include <mutex>
#include <atomic>

#include "Session.hpp"
#include <game/phase/Phase.hpp>

namespace xal { namespace game { namespace session {
    class Room: public Session {
    public:
        typedef std::string RoomID;

        static const std::string ARG__GAME_DIR;
        static const std::string GAME__SERVER_DIR_PATH;
        static const std::string GAME__CLIENT_DIR_PATH;
    
    private:
        typedef std::queue<nlohmann::json> MessagesQueue;

    public:
        Room() = default;

        void setGame(const std::string_view gameDir);

        void run();

        void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) override;

    private:
        std::mutex& getMutex(bool getA);
        MessagesQueue& getMessagesQueue(bool getA);

    private:
        std::filesystem::path m_gameDir;

        std::unique_ptr<phase::Phase> m_gamePhase;

        std::atomic_bool m_currentQueue = std::atomic_bool(true);
        std::mutex m_mutexA;
        std::mutex m_mutexB;
        MessagesQueue m_messagesQueueA;
        MessagesQueue m_messagesQueueB;

        uint m_ticks = 60;
        double m_TPS = 1.f / m_ticks;
        double m_accumulator = 0.f;
    };
} } }