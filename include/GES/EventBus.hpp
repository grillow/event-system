#pragma once
#include "IEvent.hpp"
#include "Utils/UniqueGenerator.hpp"
#include "IEventListener.hpp"

#include <utility>
#include <memory>
#include <list>
#include <map>


class EventBus final {
public:
    struct Handle final {
        friend class EventBus;

        using id_t = uint64_t;

        Handle(const Handle & other) = delete;
        Handle(Handle && other);
        Handle & operator= (Handle && other);
        ~Handle();

        void Release();
        bool Active() const;

        friend bool operator< (const Handle & left, const Handle & right);

    private:
        Handle(std::weak_ptr<EventBus> bus, const id_t id);

        std::weak_ptr<EventBus> m_bus;
        id_t m_id;
    };

public:
    static std::shared_ptr<EventBus> Create();

    EventBus(std::shared_ptr<EventBus> bus);
    EventBus(const EventBus & other) = delete;

    // Raise Event
    template <EventDerived T, typename ...Args>
    constexpr void Raise(Args&&... args) {
        Raise(std::make_unique<T>(std::forward<Args>(args)...));
    }
    void Raise(std::unique_ptr<IEvent> event);

    // Add Event Listener
    template <EventListenerBaseDerived T, typename ...Args>
    [[nodiscard]] constexpr Handle Add(Args&&... args) {
        return Add(std::make_unique<T>(std::forward<Args>(args)...));
    }
    [[nodiscard]] Handle Add(std::unique_ptr<IEventListenerBase> listener);
    
    // Remove Event Listener
    void Remove(Handle && handle);

private:
    std::weak_ptr<EventBus> m_bus;
    struct InternalHandle;
    
    std::map<
        InternalHandle,
        std::shared_ptr<IEventListenerBase>
    > m_listeners_handle;
    
    std::map<
        IEvent::Type_t,
        std::list<
            std::weak_ptr<IEventListenerBase> 
        >
    > m_listeners_type;

    UniqueGenerator<EventBus::Handle::id_t> m_generator;
};


/*
 *  EventBus::InternalHandle
 */

struct EventBus::InternalHandle final {
    explicit InternalHandle(const Handle::id_t id);
    explicit InternalHandle(const Handle & handle);

    const Handle::id_t m_id;

    friend constexpr bool operator< (const InternalHandle & left,
            const InternalHandle & right) {
        return left.m_id < right.m_id;
    }

    friend constexpr bool operator==(const InternalHandle & left,
            const InternalHandle & right) {
        return left.m_id == right.m_id;
    }
};

