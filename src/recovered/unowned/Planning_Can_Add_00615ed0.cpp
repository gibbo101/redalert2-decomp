#define RA2_COORD_EQUAL_MEMBER
// bool Planning_Can_Add() (0x00615ED0)
// While planning: whether the player's planned technos plus the selected
// technos without a token or with an empty path stay within 128; refuses
// (Planning_Refuse, MSG:PlannerMaximum) when they do not.
#include "shared/planning.hpp"
// @ref ??_C@_0BD@HJHC@MSG?3PlannerMaximum?$AA@=007ebddc

bool __fastcall Planning_Can_Add()
{
    if (unknown_flag_a767a4) {
        int total = Planning_Count(unknown_player_a35db4->ArrayIndex);
        int added = 0;
        int count = unknown_objects_a40c60.Count();
        for (int i = 0; i < count; i++) {
            ObjectClass *object = unknown_objects_a40c60[i];
            bool techno;
            if (object != 0) {
                techno = object->AbstractFlags.IsTechno;
            }
            if (object != 0 && techno) {
                PlanningTokenClass *token = Planning_Token((TechnoClass *)object);
                if (token == 0) {
                    added++;
                } else if (token->Nodes.Count() == 0) {
                    added++;
                }
            }
        }
        if (total + added > 128) {
            Planning_Refuse("MSG:PlannerMaximum");
            return false;
        }
    }
    return true;
}
