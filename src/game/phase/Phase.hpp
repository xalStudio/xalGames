#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace xal { namespace game { namespace session { class Room; } } }

namespace xal { namespace game { namespace phase {
    class Phase {
    public:
        Phase(const std::filesystem::path& luaFilePath);

        virtual void run(xal::game::session::Room* room) = 0;
    protected:
        std::filesystem::path m_luaFilePath;

        sol::state m_luaState;
    };
} } }