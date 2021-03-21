#pragma once
#include "IEvent.hpp"

#include <type_traits>

template <typename T>
struct EventHandler {
public:
    constexpr EventHandler() {
        static_assert(std::is_base_of<IEvent, T>::value, "EventHandler<T>: T must inherit from IEvent");
    }

    virtual ~EventHandler() = default;

    void Dispatch(IEvent & event) {
        OnEvent(dynamic_cast<T &>(event));
    }

    virtual void OnEvent(T & event) = 0;

};

