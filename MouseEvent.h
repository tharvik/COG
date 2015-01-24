#pragma once

#include "Event.h"
#include "Point.h"

class MouseEvent : public Event {
private:
        const Vector2D<int> position;
        
public:
        MouseEvent(const Vector2D<int>& _position);
        
        virtual Event::EventType_t getType() const;
        const Vector2D<int>& getPosition();
};
