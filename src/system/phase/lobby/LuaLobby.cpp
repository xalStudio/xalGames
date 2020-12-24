#include "LuaLobby.hpp"

#include <iostream>
#include <system_error>

#include <system/session/Room.hpp>

namespace xal { namespace system { namespace phase {
    const std::string LuaLobby::LUA_FILE = "lobby.lua";

    LuaLobby::LuaLobby(const std::filesystem::path& luaFilePath)
        : m_engine { luaFilePath }
    { }

    void LuaLobby::gameLoopRun(xal::system::session::Room* room) {
        // const auto* messagesQueue = room->getMessagesQueue();
        // const isQueueA = messagesQueue->isQueueACurrent();

        // const auto& queue = messagesQueue->getQueue(isQueueA);

        // {
        //     const std::lock_guard<std::mutex> lock(messagesQueue->getMutex(isQueueA));
        //     if (queue.empty()) {

        //     }
        // }
    }
} } }