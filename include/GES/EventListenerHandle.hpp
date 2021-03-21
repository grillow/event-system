#pragma once
#include "EventBus.hpp"

#include <cstdint>

struct EventListenerHandle final {
friend struct EventBus;
public:
    ~EventListenerHandle() {
        m_bus.RemoveEventListener(m_id);
    }

    friend bool operator< (const EventListenerHandle & left, const EventListenerHandle & right) {
        return left.m_id < right.m_id;
    }

private:
    EventListenerHandle(EventBus & bus, const uint64_t id) : m_bus(bus), m_id(id) {}
    
    EventBus & m_bus;
    const uint64_t m_id;

};

