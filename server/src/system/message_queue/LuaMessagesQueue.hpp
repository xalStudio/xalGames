#pragma once

#include "MessagesQueue.hpp"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace xal { namespace system { namespace message_queue {
    class LuaMessagesQueue: public MessagesQueue<sol::table> {
    public:
        LuaMessagesQueue() = default;

        virtual void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) override;
    };
} } }