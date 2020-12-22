#include "OnlyMessages.hpp"

#include <chrono>

namespace xal { namespace game { namespace game_loop {
    void OnlyMessages::run(GameLoop::RunFunction runFunction) {
        auto m_currentTime = std::chrono::system_clock::now();

        while (true) {
            auto timeNow = std::chrono::system_clock::now();
            double frameTime = std::chrono::duration<double>(timeNow - m_currentTime).count();
            m_currentTime = timeNow;

            runFunction();
                
            double remainingTime = std::chrono::duration<double>(m_currentTime - std::chrono::system_clock::now()).count();
            if (remainingTime > 0.f) {
                
            }
        }
    }
} } }