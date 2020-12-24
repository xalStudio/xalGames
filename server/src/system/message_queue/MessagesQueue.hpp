#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <nlohmann/json.hpp>
#include <network/WebsocketServer.hpp>
#include <websocketpp/server.hpp>

namespace xal { namespace system { namespace message_queue {
    template <typename T> 
    class MessagesQueue {
    public:
        typedef std::queue<T> Queue;

    public:
        MessagesQueue() = default;

        virtual void onMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, const nlohmann::json& message) = 0;

        std::mutex& getMutex(bool getA);
        Queue&      getQueue(bool getA);
        bool        isQueueACurrent() const;

    protected:
        std::atomic_bool m_currentQueue = std::atomic_bool(true);
        std::mutex       m_mutexA;
        std::mutex       m_mutexB;
        Queue            m_queueA;
        Queue            m_queueB;
    };

    template <typename T>
    std::mutex& MessagesQueue<T>::getMutex(bool getA) {
        return getA ? m_mutexA : m_mutexB;
    }

    template <typename T>
    MessagesQueue<T>::Queue& MessagesQueue<T>::getQueue(bool getA) {
        return getA ? m_queueA : m_queueB;
    }

    template <typename T>
    bool MessagesQueue<T>::isQueueACurrent() const {
        return m_currentQueue;
    }
} } }