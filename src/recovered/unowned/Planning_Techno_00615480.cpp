#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Techno_00615480(TechnoClass *techno, EventClass *event) (0x00615480)
// Unless the event was planned, takes the techno out of its whole path (0x006155E0),
// then clears the path's +0x1C mark. Name hypothesis kept: EventClass::Execute binds it.
#include "shared/planning.hpp"

void __fastcall Planning_Techno_00615480(TechnoClass *techno, EventClass *event)
{
    if (techno != 0) {
        PlanningTokenClass *token = Planning_Token(techno);
        if (token != 0) {
            int planned = event != 0 ? (char)event->ByteAt(0x1D) : 0;
            if (!planned && token->Get_Node_Count() > 0) {
                techno->unknown_6155e0();
            }
            token->Clear_1c();
        }
    }
}
