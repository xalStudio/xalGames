#pragma once

#include <functional>

#include <network/WebsocketServer.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

namespace xal { namespace game { namespace session {
    class Session {
    public:
        virtual void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) = 0;
    }; 
} } }