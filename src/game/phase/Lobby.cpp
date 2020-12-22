#include "Lobby.hpp"

#include <iostream>
#include <system_error>

namespace xal { namespace game { namespace phase {
    const std::string Lobby::LUA_FILE = "lobby.lua";

    Lobby::Lobby(const std::filesystem::path& luaFilePath)
        : Phase {luaFilePath}
    { }
} } }