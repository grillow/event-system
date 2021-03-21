#pragma once
#include "ISender.hpp"


struct IEvent {
public:
    IEvent(ISender & sender);
    virtual ~IEvent();

private:
    ISender & m_sender;
};

