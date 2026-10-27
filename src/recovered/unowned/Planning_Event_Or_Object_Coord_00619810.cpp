#define RA2_COORD_EQUAL_MEMBER
// CoordStruct __fastcall Planning_Event_Or_Object_Coord(EventClass const &event, AbstractClass *object) (0x00619810)
// The coordinate an event points at, or the object's when the event points
// nowhere.
#include "shared/planning.hpp"

CoordStruct __fastcall Planning_Event_Or_Object_Coord(EventClass const &event, AbstractClass *object)
{
    CoordStruct coord = Planning_Event_Coord(event);
    if (coord.X == -1 && coord.Y == -1 && coord.Z == -1 && object) {
        coord = object->unknown_slot22();
    }
    return coord;
}
