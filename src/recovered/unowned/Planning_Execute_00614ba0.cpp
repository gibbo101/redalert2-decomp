#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Execute(EventClass *event) (0x00614BA0)
// Carries out a planning event: 0x2B restarts the paths of the event's house,
// 0x2A adds the node at the 0x0C target's coordinate to the 0x07 techno's path,
// 0x2C takes the node at the 0x07 target's coordinate out of every path
// (remembering the next node for the player); any other event is an order for
// the 0x07 techno.
#include "shared/planning.hpp"
// @ref ?Planning_House@@YIHPAVTechnoClass@@@Z=00610770
// @ref ?unknown_613310@PlanningTokenClass@@QBE_NXZ=00613310
// @ref ?Planning_Path_Append@@YIXPAVTechnoClass@@PAVPlanningNodeClass@@@Z=006165a0
// @ref ?Add@?$DynamicVectorClass@PAVPlanningTokenClass@@@@QAE_NABQAVPlanningTokenClass@@@Z=0061b940
// @ref ?Is_At@PlanningNodeClass@@QBE_NUCoordStruct@@@Z=00611310
// @ref ?Planning_Add_Order@@YI_NPAVTechnoClass@@PAVEventClass@@@Z=00614ec0

// For every planning techno of a house: clears its path's loop marks, and when
// its path was not under way but its mission allows it, starts the path again.
// The same steps as Commit_Plans (0x00614850), written without its
// Commit_Unit_Orders helper: this arm expands Planning_Token, Planning_House
// and the token test inline but calls the four steps.
inline void __fastcall Planning_Restart_House(int house)
{
    int count = unknown_list_a40c20.Count();
    for (int i = 0; i < count; i++) {
        TechnoClass *techno = unknown_list_a40c20[i];
        if (house == Planning_House(techno)) {
            PlanningTokenClass *token = Planning_Token(techno);
            if (token) {
                bool started = token->unknown_613310();
                token->unknown_613a80();
                bool allows = Planning_Mission_Allows(techno);
                if (!started && allows) {
                    techno->unknown_615360();
                }
            }
        }
    }
}

static inline PlanningNodeClass *Planning_Next_On_Path(PlanningNodeClass *node)
{
    TechnoClass *owner = node->Members[0]->Owner;
    PlanningTokenClass *token = Planning_Token(owner);
    int index = Token_Node_Index(token, node);
    PlanningTokenClass *path = Planning_Token(owner);
    PlanningNodeClass *next = path->Node_At(index + 1);
    return next;
}

void __fastcall Planning_Execute(EventClass *event)
{
    if (event->Type == 0x2B) {
        Planning_Restart_House(event->House);
    } else if (event->Type == 0x2A) {
        TechnoClass *techno = event->TargetAt(0x07).As_Techno();
        if (techno) {
            AbstractClass *object = event->TargetAt(0x0C).As_Abstract();
            if (object) {
                CoordStruct coord = object->unknown_slot22();
                PlanningNodeClass *node = Planning_Find_Node(event->House, -1, coord);
                if (node) {
                    Planning_Path_Add(techno, node);
                }
            }
        }
    } else if (event->Type == 0x2C) {
        AbstractClass *object = event->TargetAt(0x07).As_Abstract();
        if (object) {
            CoordStruct coord = object->unknown_slot22();
            int house = event->House;
            PlanningNodeClass *node = Planning_Find_Node(house, -1, coord);
            if (node) {
                PlanningNodeClass *next = Planning_Next_On_Path(node);
                Planning_Remove_Node(node);
                if (next && house == unknown_player_a35db4->ArrayIndex) {
                    unknown_node_a766b0 = next;
                }
            }
        }
    } else {
        TechnoClass *techno = event->TargetAt(0x07).As_Techno();
        Planning_Add_Order(techno, event);
    }
}
