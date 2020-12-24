#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include "Engine.hpp"
#include <system/message_queue/LuaMessagesQueue.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace xal { namespace system { namespace engine {
    class LuaEngine: public Engine<message_queue::LuaMessagesQueue> {
    public:
        LuaEngine(const std::filesystem::path& luaFilePath);

        virtual void run();
    protected:
        std::filesystem::path m_luaFilePath;

        sol::state m_luaState;
    };
} } }