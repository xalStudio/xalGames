#include "Game.hpp"

#include <iostream>
#include <system_error>

namespace xal { namespace game { namespace phase {
    const std::string Game::LUA_FILE = "game.lua";

    Game::Game(const std::filesystem::path& luaFilePath)
        : Phase {luaFilePath}
    { }

    void Game::run() {
        

        
    }
} } }