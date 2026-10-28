// void TechnoClass::unknown_slot233() (0x006CD8B0, slot 233)
// Slot 71 (2) and full strength (the type's MaxStrength into +0x6C and
// +0x70); buildings also get slot 97 (0), 0x0044D070 with whether the health
// is at or below the rules' +0x1368, and the rules' +0x1BC sound at their
// centre.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_44d070@BuildingClass@@QAEXH@Z=0044d070
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

void TechnoClass::unknown_slot233()
{
    unknown_slot71(2);
    int strength = unknown_slot32()->MaxStrength;
    Strength = strength;
    unknown_70 = strength;
    if (Kind_Of() == 6) {
        unknown_slot97(0);
        ((BuildingClass *)this)->unknown_44d070(Health_Ratio() <= Rules->unknown_1368);
        Voc_Play_At(Rules->unknown_1bc, Center_Coord(), 0);
    }
}
