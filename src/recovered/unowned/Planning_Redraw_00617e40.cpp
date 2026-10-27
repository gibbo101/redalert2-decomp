#define RA2_COORD_EQUAL_MEMBER
// void Planning_Redraw() (0x00617E40)
// Forgets the nodes drawn on screen, then draws every node and every
// planning techno that belongs to the player or an ally.
#include "shared/planning.hpp"
// @ref ?Planning_Draw_Techno@@YIXPAVTechnoClass@@@Z=006182f0
// @ref ?unknown_619420@PlanningNodeClass@@QAEXXZ=00619420
// @ref ?unknown_list_a40c20@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20

void __fastcall Planning_Draw_Techno(TechnoClass *techno);

void Planning_Redraw()
{
    Planning_Clear_Drawn();
    int count = PlanningNodeClass::unknown_list_00a76628.Count();
    int i;
    for (i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a76628[i];
        if (node->House()->Is_Ally(unknown_player_a35db4)) {
            node->unknown_619420();
        }
    }
    count = unknown_list_a40c20.Count();
    for (i = 0; i < count; i++) {
        TechnoClass *techno = unknown_list_a40c20[i];
        HouseClass *house = techno->House;
        if (house->Is_Ally(unknown_player_a35db4)) {
            Planning_Draw_Techno(techno);
        }
    }
}
