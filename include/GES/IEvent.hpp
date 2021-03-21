#pragma once
#include <string>


struct IEvent {
public:
    virtual ~IEvent() = default;
    virtual std::string Type() const = 0;
};

