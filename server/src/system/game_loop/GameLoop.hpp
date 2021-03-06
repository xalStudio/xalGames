#pragma once

#include <functional>

namespace xal { namespace system { namespace game_loop {
    class GameLoop {
    public:
        typedef std::function<void()> RunFunction;

    public:
        GameLoop() = default;

        virtual void run(RunFunction runFunction) = 0;
    };
} } }