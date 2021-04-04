#pragma once
#include "IEvent.hpp"

#include <type_traits>
#include <functional>
#include <vector>
#include <map>


struct IEventListenerBase {
    virtual ~IEventListenerBase() = default;
    virtual void Receive(IEvent & event) = 0;
    virtual const std::vector<IEvent::Type_t> & Types() const = 0;
};

template <typename T>
concept EventListenerBaseDerived = std::is_base_of<IEventListenerBase, T>::value;


// helper, do not use it
struct IEventListenerResource : IEventListenerBase {
    template <EventDerived TEvent = IEvent>
    using callback_t = std::function<void(TEvent &)>;

    void Receive(IEvent & event) override final {
        m_callbacks[event.Type()](event);
    }
    
    const std::vector<IEvent::Type_t> & Types() const override final {
        return m_types;
    }

protected:
    std::vector<IEvent::Type_t> m_types;
    std::map<IEvent::Type_t, callback_t<>> m_callbacks;
};


template <EventDerived T>
struct EventListenerTemplate : virtual IEventListenerResource {
    constexpr EventListenerTemplate() {
        m_types.emplace_back(T::ID);
        m_callbacks[T::ID] = [this](IEvent & event){ OnEvent(dynamic_cast<T &>(event)); };
    }
    virtual void OnEvent(T & event) = 0;
};


template <EventDerived... T>
struct EventListener : EventListenerTemplate<T>... {
};


template <EventDerived T>
struct EventListenerLambda final : EventListener<T> {
    constexpr EventListenerLambda(IEventListenerResource::callback_t<T> callback) :
        m_callback(callback) {}

    void OnEvent(T & event) override final {
        m_callback(event);
    }

private:
    const IEventListenerResource::callback_t<T> m_callback;
};

