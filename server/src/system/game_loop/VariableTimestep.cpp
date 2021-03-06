#include "VariableTimestep.hpp"

#include <chrono>
#include <thread>

namespace xal { namespace system { namespace game_loop {
    void VariableTimestep::run(GameLoop::RunFunction runFunction) {
        while (true) {
            const auto& startTime = std::chrono::system_clock::now();

            runFunction();
                
            double elapsedTime = std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
            if (elapsedTime < m_TPS) {
                std::this_thread::sleep_for(std::chrono::duration<double>(m_TPS - elapsedTime));
            }
        }
    }
} } }