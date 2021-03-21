#include "IEvent.hpp"

IEvent::IEvent(ISender & sender) : m_sender(sender) {}

IEvent::~IEvent() {}

