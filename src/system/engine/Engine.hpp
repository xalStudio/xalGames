#pragma once

#include <filesystem>
#include <string_view>
#include <string>

namespace xal { namespace system { namespace engine {
    template <typename MessagesQueue>
    class Engine {
    public:
        Engine() = default;

        virtual void run() = 0;
    protected:
        MessagesQueue m_messagesQueue;
    };
} } }