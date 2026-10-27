#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Unlist_Techno(TechnoClass *techno) (0x00614550)
// Takes a techno out of the planning list, lowering its house's counter.
#include "shared/planning.hpp"

void __fastcall Planning_Unlist_Techno(TechnoClass *techno)
{
    int house = techno->House->ArrayIndex;
    if (techno->House->Unknown_004F52B0() && unknown_player_a35db4) {
        house = unknown_player_a35db4->ArrayIndex;
    }
    Planning_Uncount(house);
    PlanningLists::unknown_list_00a76700.Delete(techno);
}
