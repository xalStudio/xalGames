#include "Game.hpp"

#include <iostream>
#include <system_error>

#include <game/session/Room.hpp>
#include <game/game_loop/OnlyMessages.hpp>

namespace xal { namespace game { namespace phase {
    const std::string Game::LUA_FILE = "game.lua";

    Game::Game(const std::filesystem::path& luaFilePath)
        : Phase {luaFilePath}
    { }

    void Game::run(xal::game::session::Room* room) {
        game_loop::OnlyMessages gameLoop;

        gameLoop.run([this, room](){

        });
    }
} } }