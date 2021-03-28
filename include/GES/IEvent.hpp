#pragma once
#include <type_traits>
#include <cstdint>


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

