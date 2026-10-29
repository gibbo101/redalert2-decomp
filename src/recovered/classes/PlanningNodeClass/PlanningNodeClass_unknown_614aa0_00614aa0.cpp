#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_614aa0() (0x00614AA0)
// Sends the player's type 0x2C event about the object the node's first
// order points at.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_614aa0()
{
    EventClass event = *Members[0]->Event;
    PlanningEventTargets const *view = (PlanningEventTargets const *)&event;
    TargetClass const *reference;
    if (view->Target_0e.Kind) {
        reference = &view->Target_0e;
    } else if (view->Target_18.Kind) {
        reference = &view->Target_18;
    } else if (view->Target_13.Kind) {
        reference = &view->Target_13;
    } else {
        return;
    }
    AbstractClass *object = reference->As_Abstract();
    if (object) {
        EventClass send(unknown_player_a35db4->ArrayIndex, 0x2C, TargetClass(object));
        Unknown_0062E670(send);
    }
}
