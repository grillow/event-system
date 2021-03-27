#pragma once
#include <cstdint>
#include <memory>

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
    EventListenerHandle(std::weak_ptr<EventBus> bus, const uint64_t id);
    
private:
    std::weak_ptr<EventBus> m_bus;
    const uint64_t m_id;

};

