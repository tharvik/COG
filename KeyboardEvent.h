#pragma once

#include "Event.h"

class KeyboardEvent : public Event {
        const int key; // TODO make more friendly
public:
        KeyboardEvent(const int _key);
        
        virtual Event::EventType_t getType() const;
        int getKey();
};