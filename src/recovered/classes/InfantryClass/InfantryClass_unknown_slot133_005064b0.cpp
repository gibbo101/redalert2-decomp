// int InfantryClass::unknown_slot133() (0x005064B0, slot 133)
// While deploying (27-30): clear the target when the owner's house check
// (0x004F52F0) holds (1), or without UndeployDelay play action 31 and wait
// its frame count; otherwise FootClass's.
#include "shared/infantry.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_slot133@FootClass@@UAEHXZ=004c38d0

int InfantryClass::unknown_slot133()
{
    if (Sequence == 27 || Sequence == 28 || Sequence == 29 || Sequence == 30) {
        if (Owning_House()->Unknown_004F52F0()) {
            unknown_slot260(0, 1);
            return 1;
        }
        if (Type->UndeployDelay <= -1) {
            unknown_slot311(31, 0, 0);
            return Type->DoControls[31].Count;
        }
    }
    return FootClass::unknown_slot133();
}
