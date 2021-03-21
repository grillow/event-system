#pragma once
#include <cstdint>

struct EventBus;

struct EventListenerHandle final {
friend struct EventBus;
public:
    ~EventListenerHandle();

    friend bool operator< (const EventListenerHandle & left,
                           const EventListenerHandle & right);

private:
    EventListenerHandle(EventBus & bus, const uint64_t id);
    
    EventBus & m_bus;
    const uint64_t m_id;

};

