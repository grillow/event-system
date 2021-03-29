#pragma once
#include <cstdint>
#include <memory>

struct EventBus;

struct EventListenerHandle final {
friend struct EventBus;
    using id_t = uint64_t;

    EventListenerHandle(const EventListenerHandle & other) = delete;
    EventListenerHandle(EventListenerHandle && other);
    ~EventListenerHandle();

    void Release();
    bool Active() const;

    friend bool operator< (const EventListenerHandle & left,
                           const EventListenerHandle & right);

private:
    EventListenerHandle(std::weak_ptr<EventBus> bus, const id_t id);
    
    std::weak_ptr<EventBus> m_bus;
    const id_t m_id;
};

