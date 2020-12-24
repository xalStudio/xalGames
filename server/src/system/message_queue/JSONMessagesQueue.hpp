#pragma once

#include "MessagesQueue.hpp"

namespace xal { namespace system { namespace message_queue {
    class JSONMessagesQueue: public MessagesQueue<nlohmann::json> {
    public:
        JSONMessagesQueue() = default;

        virtual void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message);
    };
} } }