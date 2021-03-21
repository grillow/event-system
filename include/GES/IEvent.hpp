#pragma once
#include <string>


struct IEvent {
public:
    virtual ~IEvent();
    virtual std::string Type() = 0;
};

