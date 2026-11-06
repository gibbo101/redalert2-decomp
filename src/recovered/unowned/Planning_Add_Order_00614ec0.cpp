#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Add_Order(TechnoClass *techno, EventClass *event) (0x00614EC0)
// Plans an order for a techno: adds it to the node at the order's coordinate,
// or to a new node, unless the order or the techno's path refuses it.
#include "shared/planning.hpp"
// @ref ?Planning_Cell_Mission@@YI_NHVTargetClass@@@Z=006159e0
// @ref ?Last_Node@PlanningTokenClass@@QBEPAVPlanningNodeClass@@XZ=00613c50
// @ref ??0?$DynamicVectorClass@PAVPlanningMemberClass@@@@QAE@IPBQAVPlanningMemberClass@@@Z=0061ac80
// @ref ??0?$DynamicVectorClass@PAVPlanningBranchClass@@@@QAE@IPBQAVPlanningBranchClass@@@Z=0061af90
// @ref ??_C@_0BA@BPML@MSG?3NodeMaximum?$AA@=007ebd04
// @ref ??_C@_0BJ@DFJC@MSG?3PostContinualCommand?$AA@=007ebd14
// @ref ??_C@_0BL@ONIM@MSG?3PostTerminatingCommand?$AA@=007ebd30
// @ref ??_C@_0N@FMPE@MSG?3PostLoop?$AA@=007ebd60
// @ref ?Planning_Order_Kind@@YIHPAVTechnoClass@@PBUPlanningEventTargets@@@Z=00615a80

// Raises a house's counter (0x00616D00).
inline void __fastcall Planning_Recount(int house)
{
    if (Planning_Valid_House(house)) {
        unknown_counts_a76684[house]++;
    }
}

// The path has closed a loop.
inline bool Planning_Token_Looped(PlanningTokenClass *token)
{
    return token->Loop_Past_Start() || token->Loop_At_Start();
}

// Puts the techno on the node: with the members of its path's last node, or alone.
inline void __fastcall Planning_Attach_Order(PlanningNodeClass *const &node, PlanningTokenClass *token, TechnoClass *techno, EventClass *event)
{
    PlanningNodeClass *last = token->Last_Node();
    if (last) {
        Planning_Copy_Members(node, last, *event);
    } else {
        node->Add_Member(techno, *event);
    }
}

bool __fastcall Planning_Add_Order(TechnoClass *techno, EventClass *event)
{
    if (!techno) {
        return false;
    }
    bool player = event->House == unknown_player_a35db4->ArrayIndex;
    CoordStruct const &coord = Planning_Event_Coord(*event);
    if (coord == CoordStruct(-1, -1, -1)) {
        return false;
    }
    int id = event->Frame;
    PlanningNodeClass *node = Planning_Find_Node(event->House, id, coord);
    if (node && node->Has_Member(techno)) {
        return true;
    }
    int kind = Planning_Order_Kind(techno, (PlanningEventTargets const *)event);
    if (kind != -1) {
        if (!player) {
            return false;
        }
        if (kind == 0) {
            Planning_Refuse_Order(event);
        } else if (kind == 1) {
            Planning_Refuse("MSG:PostTerminatingCommand");
        } else if (kind == 2) {
            Planning_Refuse("MSG:PostContinualCommand");
        }
        return false;
    }
    PlanningTokenClass *token = Planning_Token(techno);
    if (!token) {
        token = Planning_New_Token(techno);
    }
    if (player) {
        int result = Planning_Event_Result(token, (PlanningEventTargets const *)event);
        if (result != -1) {
            Planning_Set_a76750(result);
        }
    }
    if (Planning_Token_Looped(token)) {
        if (player) {
            Planning_Refuse("MSG:PostLoop");
        }
        return false;
    }
    if (token->Get_Node_Count() == 0) {
        PlanningLists::unknown_list_00a76700.Add(techno);
        Planning_Recount(event->House);
    } else if (token->Get_Node_Count() == 16) {
        if (player) {
            Planning_Refuse("MSG:NodeMaximum");
        }
        return false;
    }
    if (!node) {
        node = new PlanningNodeClass(event->Frame);
        PlanningNodeClass::unknown_list_00a76628.Add(node);
    }
    Planning_Attach_Order(node, token, techno, event);
    if (player) {
        Voc_Play(Rules->unknown_1d0, 1.0f, 0x2000, 0);
    }
    return true;
}
