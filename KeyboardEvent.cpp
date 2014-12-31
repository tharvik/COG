#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(const int _key) : key(_key)
{}

int KeyboardEvent::getKey()
{
        return key;
}

Event::EventType_t KeyboardEvent::getType() const
{
        return Event::KEYBOARD;
}
