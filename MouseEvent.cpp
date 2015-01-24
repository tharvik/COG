#include "MouseEvent.h"

MouseEvent::MouseEvent(const Vector2D<int>& _position) : position(_position)
{}

Event::EventType_t MouseEvent::getType() const
{
        return Event::MOUSE;
}

const Vector2D<int>& MouseEvent::getPosition()
{
        return position;
}