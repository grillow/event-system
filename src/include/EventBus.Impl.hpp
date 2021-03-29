#pragma once
#include "EventBus.hpp"
#include "UniqueGenerator.hpp"

#include <map>
#include <list>
#include <utility>


struct EventBus::Impl {
friend class EventBus;
public:
    Impl();
    
    void Raise(std::unique_ptr<IEvent> event);
    
    EventBus::Handle Add(std::unique_ptr<IEventListenerBase> listener);
    
    void Remove(EventBus::Handle && handle);

private:
    struct Handle;

    std::weak_ptr<EventBus> m_bus;
    
    std::map<
        Handle,
        std::shared_ptr<IEventListenerBase>
    > m_listeners_handle;
    
    std::map<
        IEvent::Type_t,
        std::list<
            std::weak_ptr<IEventListenerBase> 
        >
    > m_listeners_type;

private:
    UniqueGenerator<EventBus::Handle::id_t> m_generator;
};


struct EventBus::Impl::Handle final {
    explicit Handle(const EventBus::Handle::id_t id);
    explicit Handle(const EventBus::Handle & handle);

    const EventBus::Handle::id_t m_id;

public:
    friend constexpr bool operator< (const Handle & left,
            const Handle & right) {
        return left.m_id < right.m_id;
    }

    friend constexpr bool operator==(const Handle & left,
            const Handle & right) {
        return left.m_id == right.m_id;
    }
};

