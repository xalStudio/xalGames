#pragma once

#include "GameLoop.hpp"

namespace xal { namespace system { namespace game_loop {
    class VariableTimestep: public GameLoop {
    public:
        VariableTimestep() = default;

        void run(GameLoop::RunFunction runFunction) override;

    private:
        uint   m_ticks = 60;
        double m_TPS = 1.f / m_ticks;
    };
} } }