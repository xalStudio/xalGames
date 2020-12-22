#include "Lobby.hpp"

#include <iostream>
#include <system_error>

#include <game/session/Room.hpp>
#include <game/game_loop/OnlyMessages.hpp>

namespace xal { namespace game { namespace phase {
    const std::string Lobby::LUA_FILE = "lobby.lua";

    Lobby::Lobby(const std::filesystem::path& luaFilePath)
        : Phase {luaFilePath}
    { }

    void Lobby::run(xal::game::session::Room* room) {
        game_loop::OnlyMessages gameLoop;

        gameLoop.run([&, this]{

        });
    }
} } }