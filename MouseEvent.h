#pragma once

#include "Event.h"
#include "Point.h"

class MouseEvent : public Event {
private:
        const Point<int> position;
        
public:
        MouseEvent(const Point<int>& _position);
        
        virtual Event::EventType_t getType() const;
        const Point<int>& getPosition();
};
