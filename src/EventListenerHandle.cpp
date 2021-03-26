#include "EventListenerHandle.hpp"
#include "EventBus.hpp"
#include "EventBus.Impl.hpp"


EventListenerHandle::EventListenerHandle(EventListenerHandle && other) :
    EventListenerHandle(std::shared_ptr<EventBus>(other.m_bus), other.m_id) {
    other.m_bus = std::shared_ptr<EventBus>(nullptr);
}


EventListenerHandle::~EventListenerHandle() {
    if (auto bus = m_bus.lock()) {
        bus->Remove(std::move(*this));
    }
}


bool operator< (const EventListenerHandle & left,
                const EventListenerHandle & right) {
    return left.m_id < right.m_id;
}


EventListenerHandle::EventListenerHandle(std::shared_ptr<EventBus> bus, const uint64_t id) :
        m_bus(bus),
        m_id(id)
    {}



/*
 *  Hidden
 */

EventBus::Impl::EventListenerHandleHidden::EventListenerHandleHidden(const uint64_t id) :
        m_id(id)
    {}

EventBus::Impl::EventListenerHandleHidden::EventListenerHandleHidden(const EventListenerHandle & handle) :
        m_id(handle.m_id)
    {}

