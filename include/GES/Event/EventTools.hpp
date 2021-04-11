#pragma once
#include "EventBase.hpp"

#include <string_view>
#include <functional>

namespace Event {

    template <typename T>
    struct EventTemplate : IEvent {
        /*constexpr*/ static inline const Type_t ID = typeid(T).name();
        Type_t Type() const override final {
            return ID;
        }
    };

}

