#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include "Phase.hpp"


namespace xal { namespace game { namespace phase {
    class Lobby: public Phase {
    public:
        struct BaseSettings {
            uint minimumPlayers;
            uint maximumPlayers;
            std::string gameName;
        };

    public:
        static const std::string LUA_FILE;

    public:
        Lobby(const std::filesystem::path& luaFilePath);

        void run(xal::game::session::Room* room) override;
    };
} } }