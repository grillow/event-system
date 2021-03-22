#pragma once
#include "IEvent.hpp"

#include <type_traits>


struct IEventListenerBase {
    virtual ~IEventListenerBase() = default;
    virtual void Receive(IEvent & event) = 0;
    virtual std::string Type() const = 0;
};


template <typename T>
struct IEventListener : IEventListenerBase {
public:
    constexpr IEventListener() {
        static_assert(std::is_base_of<IEvent, T>::value,
                "IEventListener<T>: T must inherit from IEvent");
    }

    void Receive(IEvent & event) override {
        OnEvent(dynamic_cast<T &>(event));
    }

    virtual void OnEvent(T & event) = 0;

};

