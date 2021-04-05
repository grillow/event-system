#pragma once
#include <type_traits>
#include <string_view>
#include <functional>
#include <cstdint>

namespace Event {

    // base interface
    struct IEvent {
        using Type_t = uint64_t;
        virtual ~IEvent() = default;
        virtual Type_t Type() const = 0;
    };


    template <typename T>
    concept EventDerived = std::is_base_of<IEvent, T>::value;


    // tools
    /*constexpr*/ inline IEvent::Type_t stot (std::string_view eventName) {
        return std::hash<std::string_view>{}(eventName);
    }

    template <typename T>
    struct EventTemplate : IEvent {
        static inline const Type_t ID = stot( typeid(T).name() );
        Type_t Type() const override final {
            return ID;
        }
    };

}

