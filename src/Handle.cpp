#include "Bus.hpp"

using namespace Event;

/*
 *  Bus::Handle
 */

Bus::Handle::Handle(Bus::Handle && other) :
    Bus::Handle(other.m_bus, other.m_id) {
    other.m_bus = std::shared_ptr<Bus>(nullptr);
}

Bus::Handle & Bus::Handle::operator= (Bus::Handle && other) {
    m_bus = other.m_bus;
    m_id  = other.m_id;

    other.m_bus = std::shared_ptr<Bus>(nullptr);

    return *this;
}

void Bus::Handle::Release() {
    if (auto bus = m_bus.lock()) {
        bus->Remove(std::move(*this));
    }
}

bool Bus::Handle::Active() const {
    return !m_bus.expired();
}

Bus::Handle::~Handle() {
    Release();
    m_bus = std::shared_ptr<Bus>(nullptr);
}


Bus::Handle::Handle(std::weak_ptr<Bus> bus, const id_t id) :
        m_bus(bus),
        m_id(id)
    {}


/*
 *  Bus::InternalHandle
 */

Bus::InternalHandle::InternalHandle(
        const Bus::Handle::id_t id) :
        m_id(id)
    {}

Bus::InternalHandle::InternalHandle(
        const Bus::Handle & handle) :
        m_id(handle.m_id)
    {}

