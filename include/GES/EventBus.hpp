#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"

#include <memory>


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

    ~EventBus();

    EventBus(const EventBus & other) = delete;

    template <EventDerived T, typename ...Args>
    constexpr void Raise(Args&&... args) {
        Raise(std::make_unique<T>(std::forward<Args>(args)...));
    }
    void Raise(std::unique_ptr<IEvent> event);

    template <EventListenerBaseDerived T, typename ...Args>
    [[nodiscard]] constexpr Handle Add(Args&&... args) {
        return Add(std::make_unique<T>(std::forward<Args>(args)...));
    }
    [[nodiscard]] Handle Add(std::unique_ptr<IEventListenerBase> listener);
    
    void Remove(Handle && handle);

private:
    struct Impl;

public:
    EventBus(std::unique_ptr<EventBus::Impl> impl); // could not manage to make it private

private:
    std::unique_ptr<EventBus::Impl> m_pimpl;

};

