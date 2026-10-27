#define RA2_COORD_EQUAL_MEMBER
// Point2D __fastcall Planning_Event_Pixel(EventClass const *event, AbstractClass *object) (0x00619FA0)
// The screen pixel an event points at (the object's when it points nowhere);
// (-1, -1) without an event.
#include "shared/planning.hpp"

Point2D __fastcall Planning_Event_Pixel(EventClass const *event, AbstractClass *object)
{
    Point2D pixel(-1, -1);
    if (event) {
        EventClass copy = *event;
        CoordStruct coord = Planning_Event_Or_Object_Coord(copy, object);
        pixel = Planning_Coord_Pixel(coord);
    }
    return pixel;
}
