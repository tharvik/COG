#pragma once

#include "Event.h"

class RefreshEvent : public Event {
public:
        typedef enum {
                IMAGE =   1 << 0,
                LEVEL =   1 << 1,
                PHYSICS = 1 << 2
        } RefreshType_t;
        
        RefreshEvent(int _type);
        
        virtual Event::EventType_t getType() const;
        virtual int getRefreshType() const;
        
private:
        const int type;
};
