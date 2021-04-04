#pragma once
#include <type_traits>
#include <functional>
#include <cstdint>
#include <string>


struct IEvent {
    using Type_t = uint64_t;
    virtual ~IEvent() = default;
    virtual Type_t Type() const = 0;
};


template <typename T>
concept EventDerived = std::is_base_of<IEvent, T>::value;


template <typename T>
struct IEventTemplate : IEvent {
    static const Type_t ID;
    Type_t Type() const override final {
        return ID;
    }
};

/*constexpr*/ inline IEvent::Type_t operator""_t (const char * eventName,
        const std::size_t size) {
    return std::hash<std::string>{}(std::string(eventName, size));
}

