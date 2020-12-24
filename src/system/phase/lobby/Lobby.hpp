#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include <system/phase/Phase.hpp>

namespace xal { namespace system { namespace session { class Room; } } }

namespace xal { namespace system { namespace phase {
    class Lobby: public Phase {
    public:
        struct BaseSettings {
            uint minimumPlayers;
            uint maximumPlayers;
            std::string gameName;
        };

    public:
        Lobby() = default;

        void run(xal::system::session::Room* room) override;

    protected:
        virtual void gameLoopRun(xal::system::session::Room* room) = 0;
    };
} } }