#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Send_Pair(AbstractClass *source, PlanningNodeClass *node) (0x00616280)
// Sends the player's type 0x2A event naming the source and the object the
// node's first order points at.
#include "shared/planning.hpp"
// @ref ??0EventClass@@QAE@HHVTargetClass@@0@Z=004b6090

void __fastcall Planning_Send_Pair(AbstractClass *source, PlanningNodeClass *node)
{
    EventClass event = *node->Members[0]->Event;
    PlanningEventTargets const *view = (PlanningEventTargets const *)&event;
    UnknownTarget const *reference;
    if (view->Target_0e.unknown_4) {
        reference = &view->Target_0e;
    } else if (view->Target_18.unknown_4) {
        reference = &view->Target_18;
    } else if (view->Target_13.unknown_4) {
        reference = &view->Target_13;
    } else {
        return;
    }
    AbstractClass *object = reference->Unknown_006B5810();
    if (object) {
        EventClass send(unknown_player_a35db4->ArrayIndex, 0x2A, TargetClass(source), TargetClass(object));
        Unknown_0062E670(send);
    }
}
