// EventClass::EventClass(int house, long a) (0x004B5EB0): event type 0x18 with one long.
#include "shared/event.hpp"
// @ref ?Frame@@3HA=00a40d2c

EventClass::EventClass(int house, long a)
{
    if (house >= 0) {
        House = house;
        Type = 0x18;
        LongAt(0x07) = a;
        Frame = ::Frame;
        return;
    }
    House = 0xFF;
    Type = 0;
    Frame = ::Frame;
}
