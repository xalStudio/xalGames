#include "JSONMessagesQueue.hpp"

namespace xal { namespace system { namespace message_queue {
    void JSONMessagesQueue::onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) {
        const std::lock_guard<std::mutex> lock(getMutex(!m_currentQueue));

        getQueue(!m_currentQueue).push(message);
    }
} } }