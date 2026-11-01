// RGBClass RadarEventClass::Get_Max_Color() const -- 0x0063C490 (TS revent.cpp)
// The bright end of the event's colour swing, by event type.
#include "shared/radar_event_class.hpp"

RGBClass RadarEventClass::Get_Max_Color() const
{
    switch (Type) {
        case 0:
        case 3:
        case 4:
            return RGBClass(255, 0, 255);
        case 1:
        case 2:
        case 11:
        case 12:
            return RGBClass(255, 255, 0);
        case 5:
            return RGBClass(0, 255, 255);
        default:
            return RGBClass(0, 0, 0);
    }
}
