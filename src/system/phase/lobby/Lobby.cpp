#include "Lobby.hpp"

#include <system/session/Room.hpp>
#include <system/game_loop/VariableTimestep.hpp>

namespace xal { namespace system { namespace phase {
    void Lobby::run(xal::system::session::Room* room) {
        game_loop::VariableTimestep gameLoop;
        gameLoop.run([&, this](){ gameLoopRun(room); });
    }
} } }