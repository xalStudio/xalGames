#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include <system/engine/LuaEngine.hpp>

#include "Lobby.hpp"

namespace xal { namespace system { namespace session { class Room; } } }

namespace xal { namespace system { namespace phase {
    class LuaLobby: public Lobby {
    public:
        static const std::string LUA_FILE;

    public:
        LuaLobby(const std::filesystem::path& luaFilePath);

    protected:
        virtual void gameLoopRun(xal::system::session::Room* room) override;

    protected:
        engine::LuaEngine m_engine;
    };
} } }