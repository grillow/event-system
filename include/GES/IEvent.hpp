#pragma once
#include <string>

struct IEvent {
public:
    virtual ~IEvent() = default;
    virtual std::string Type() const = 0;
};

template <typename T>
concept EventDerived = std::is_base_of<IEvent, T>::value;


template <typename T>
struct IEventTemplate : IEvent {
    static const std::string Name;
    std::string Type() const override {
        return Name;
    }
};

