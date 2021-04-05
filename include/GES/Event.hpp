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
    template <typename T>
    struct EventTemplate : IEvent {
        static const Type_t ID;
        Type_t Type() const override final {
            return ID;
        }
    };

    /*constexpr*/ inline IEvent::Type_t operator""_t (const char * eventName,
            const std::size_t size) {
        return std::hash<std::string_view>{}(std::string_view(eventName, size));
    }

}

