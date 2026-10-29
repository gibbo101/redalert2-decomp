// EventClass::EventClass(int house, SpecialClass data) (0x004B5EB0): event type 0x18 (SPECIAL),
// the game options word (Red Alert's EventClass(SpecialClass)).
#include "shared/event.hpp"
#include "shared/special.hpp"
// @ref ?Frame@@3HA=00a40d2c

EventClass::EventClass(int house, SpecialClass data)
{
    if (house >= 0) {
        House = house;
        Type = 0x18;
        SpecialAt(0x07) = data;
        Frame = ::Frame;
        return;
    }
    House = 0xFF;
    Type = 0;
    Frame = ::Frame;
}
