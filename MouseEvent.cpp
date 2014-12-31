#include "MouseEvent.h"

MouseEvent::MouseEvent(const Point<int>& _position) : position(_position)
{}

Event::EventType_t MouseEvent::getType() const
{
        return Event::MOUSE;
}

const Point<int>& MouseEvent::getPosition()
{
        return position;
}