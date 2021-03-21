#include "EventListenerHandle.hpp"
#include "EventBus.hpp"


EventListenerHandle::~EventListenerHandle() {
    m_bus.Remove(*this);
}


bool operator< (const EventListenerHandle & left,
                const EventListenerHandle & right) {
    return left.m_id < right.m_id;
}


EventListenerHandle::EventListenerHandle(EventBus & bus, const uint64_t id) :
        m_bus(bus),
        m_id(id)
    {}

