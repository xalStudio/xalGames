#pragma once

#include "Session.hpp"

namespace xal { namespace system { namespace session {
    class RoomPool: public Session {
    public:
        void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) override;
    };
} } }