#pragma once

#include <string>

class Event { // Abstract pure
public:
        typedef enum {
                KEYBOARD,
                MOUSE,
                REFRESH,
                CUSTOM
        } EventType_t;
        
        virtual EventType_t getType() const = 0;
};
