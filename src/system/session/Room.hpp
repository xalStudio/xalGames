#pragma once

#include <string_view>
#include <string>
#include <memory>
#include <filesystem>
#include <queue>
#include <mutex>
#include <atomic>

#include "Session.hpp"
#include <system/phase/Phase.hpp>

namespace xal { namespace system { namespace phase {
    class Lobby;
    // class Game;
} } }

namespace xal { namespace system { namespace session {
    class Room: public Session {
    public:
        typedef std::string RoomID;

        static const std::string ARG__GAME_DIR;
        static const std::string GAME__SERVER_DIR_PATH;
        static const std::string GAME__CLIENT_DIR_PATH;

    public:
        Room() = default;

        void setGame(const std::string_view gameDir);

        void run();

        void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) override;

    protected:
        friend class Lobby;
        // friend class Game;

    private:
        std::filesystem::path m_gameDir;

        std::unique_ptr<phase::Phase> m_gamePhase;
    };
} } }