#pragma once
#include "EventBase.hpp"

#include <string_view>
#include <functional>

namespace Event {

    /*constexpr*/ inline IEvent::Type_t stot (std::string_view eventName) {
        return std::hash<std::string_view>{}(eventName);
    }

    template <typename T>
    struct EventTemplate : IEvent {
        /*constexpr*/ static inline const Type_t ID = stot( typeid(T).name() );
        Type_t Type() const override final {
            return ID;
        }
    };

}

