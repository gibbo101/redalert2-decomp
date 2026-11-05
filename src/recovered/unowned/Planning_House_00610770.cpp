#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_House(TechnoClass *techno) (0x00610770)
// The house a techno plans for: its own, or the player's when its side is
// human-controlled.
#include "shared/planning.hpp"

int __fastcall Planning_House(TechnoClass *techno)
{
    HouseClass *side = techno->House;
    int house = side->ArrayIndex;
    if (side->Unknown_004F52B0() && unknown_player_a35db4) {
        house = unknown_player_a35db4->ArrayIndex;
    }
    return house;
}
