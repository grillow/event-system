#pragma once
#include "Priority.hpp"
#include "IEvent.hpp"

#include <type_traits>
#include <functional>
#include <vector>
#include <map>


struct IEventListenerBase {
    virtual ~IEventListenerBase() = default;
    virtual void Receive(IEvent & event) = 0;
    virtual std::vector<IEvent::Type_t> Types() const = 0;
    virtual Priority::DefaultPrioritySystem Priority() const = 0;
};

template <typename T>
concept EventListenerBaseDerived = std::is_base_of<IEvent, T>::value;


// helper, do not use it
struct IEventListenerResource : IEventListenerBase {
    template <EventDerived T = IEvent>
    using callback_t = std::function<void(T &)>;
   
    IEventListenerResource(
            const Priority::DefaultPrioritySystem priority =
            Priority::DefaultPrioritySystem::DEFAULT)
        : m_priority(priority){}

    void Receive(IEvent & event) override final {
        m_callbacks[event.Type()](event);
    }
    
    std::vector<IEvent::Type_t> Types() const override final {
        return m_types;
    }

    Priority::DefaultPrioritySystem Priority() const override final {
        return m_priority;
    }

protected:
    std::vector<IEvent::Type_t> m_types;
    std::map<IEvent::Type_t, callback_t<>> m_callbacks;
    const Priority::DefaultPrioritySystem m_priority;
};


template <EventDerived T>
struct IEventListener : virtual IEventListenerResource {
    constexpr IEventListener(){
        m_types.emplace_back(T::ID);
        m_callbacks[T::ID] = [this](IEvent & event){ OnEvent(dynamic_cast<T &>(event)); };
    }
    
    virtual void OnEvent(T & event) = 0;
};


template <EventDerived T>
struct IEventListenerLambda : IEventListener<T> {
    constexpr IEventListenerLambda(IEventListenerResource::callback_t<T> callback) :
        m_callback(callback) {}

    void OnEvent(T & event) override final {
        m_callback(event);
    }

private:
    const IEventListenerResource::callback_t<T> m_callback;
};

