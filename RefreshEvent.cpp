#include "RefreshEvent.h"

RefreshEvent::RefreshEvent(int _type) : Event(), type(_type)
{}

Event::EventType_t RefreshEvent::getType() const
{
        return Event::REFRESH;
}

int RefreshEvent::getRefreshType() const
{
        return type;
}