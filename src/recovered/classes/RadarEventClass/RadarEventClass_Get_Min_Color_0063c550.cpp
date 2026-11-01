// RGBClass RadarEventClass::Get_Min_Color() const -- 0x0063C550 (TS revent.cpp)
// The dark end of the event's colour swing, by event type.
#include "shared/radar_event_class.hpp"

RGBClass RadarEventClass::Get_Min_Color() const
{
    switch (Type) {
        case 0:
        case 3:
        case 4:
            return RGBClass(128, 0, 128);
        case 1:
        case 2:
        case 11:
        case 12:
            return RGBClass(128, 128, 0);
        case 5:
            return RGBClass(0, 128, 128);
        default:
            return RGBClass(0, 0, 0);
    }
}
