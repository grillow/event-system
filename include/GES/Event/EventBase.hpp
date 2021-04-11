#pragma once
#include <type_traits>
#include <string_view>

namespace Event {

    struct IEvent {
        using Type_t = std::string_view;
        virtual ~IEvent() = default;
        virtual Type_t Type() const = 0;
    };


    template <typename T>
    concept EventDerived = std::is_base_of<IEvent, T>::value;

}

