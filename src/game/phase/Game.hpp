#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include "Phase.hpp"

namespace xal { namespace game { namespace phase {
    class Game: public Phase {
    public:
        static const std::string LUA_FILE;

    public:
        Game(const std::filesystem::path& luaFilePath);

        void run();

    private:
        sol::state m_luaState;
    };
} } }