#include "Game.hpp"

#include <iostream>
#include <system_error>

#include <system/session/Room.hpp>
#include <system/game_loop/VariableTimestep.hpp>

namespace xal { namespace system { namespace phase {
    const std::string Game::LUA_FILE = "game.lua";

    Game::Game(const std::filesystem::path& luaFilePath)
        : Phase {luaFilePath}
    { }

    void Game::run(xal::game::session::Room* room) {
        game_loop::VariableTimestep gameLoop;

        gameLoop.run([this, room](){

        });
    }
} } }