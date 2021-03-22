#pragma once
#include <cstdint>

struct EventBus;

struct EventListenerHandle final {
friend struct EventBus;
public:
    EventListenerHandle(const EventListenerHandle & other) = delete;
    EventListenerHandle(EventListenerHandle && other);
    ~EventListenerHandle();

    friend bool operator< (const EventListenerHandle & left,
                           const EventListenerHandle & right);

private:
    EventListenerHandle(EventBus & bus, const uint64_t id);
    
private:
    EventBus & m_bus;
    const uint64_t m_id;

    bool m_destroyed;

};

