#define RA2_COORD_EQUAL_MEMBER
// CoordStruct __fastcall Planning_Event_Coord(EventClass const &event) (0x00610980)
// For a type-4 event, the slot-22 coordinate of the first set reference
// (+0x0E, then +0x18, then +0x13); (-1, -1, -1) otherwise.
#include "shared/planning.hpp"

CoordStruct __fastcall Planning_Event_Coord(EventClass const &event)
{
    if (event.Type == 4) {
        PlanningEventTargets const &targets = (PlanningEventTargets const &)event;
        if (targets.Target_0e.Kind) {
            AbstractClass *object = targets.Target_0e.As_Abstract();
            if (object) {
                return object->unknown_slot22();
            }
        } else if (targets.Target_18.Kind) {
            AbstractClass *object = targets.Target_18.As_Abstract();
            if (object) {
                return object->unknown_slot22();
            }
        } else if (targets.Target_13.Kind) {
            AbstractClass *object = targets.Target_13.As_Abstract();
            if (object) {
                return object->unknown_slot22();
            }
        }
    }
    return CoordStruct(-1, -1, -1);
}
