#pragma once

#include "Session.hpp"

namespace xal { namespace game { namespace session {
    class RoomPool: public Session {
    public:
        void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) override;
    };
} } }