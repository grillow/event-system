#pragma once
#include "IEvent.hpp"

#include <type_traits>
#include <functional>
#include <vector>
#include <map>


struct IEventListenerBase {
    virtual ~IEventListenerBase() = default;
    virtual void Receive(IEvent & event) = 0;
    virtual std::vector<IEvent::Type_t> Types() const = 0;
};

// helper, do not use it
struct IEventListenerResource : IEventListenerBase {
    std::vector<IEvent::Type_t> Types() const override final {
        return m_types;
    }
    
    void Receive(IEvent & event) override final {
        m_callbacks[event.Type()](event);
    }

protected:
    std::vector<IEvent::Type_t> m_types;
    std::map<IEvent::Type_t, std::function<void(IEvent &)>> m_callbacks;
};


template <EventDerived T>
struct IEventListener : virtual IEventListenerResource {
    constexpr IEventListener() {
        m_types.emplace_back(T::ID);
        m_callbacks[T::ID] = [this](IEvent & event){ OnEvent(dynamic_cast<T &>(event)); };
    }

    virtual void OnEvent(T & event) = 0;
};


template <EventDerived T>
struct IEventListenerLambda : IEventListener<T> {
    constexpr IEventListenerLambda(std::function<void(T &)> callback) : m_callback(callback) {}

    void OnEvent(T & event) override final {
        m_callback(event);
    }

private:
    const std::function<void(T &)> m_callback;
};

