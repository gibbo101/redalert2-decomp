// void BuildingClass::unknown_slot97(int mode) (0x00443680)
// Sets the repair flag (unknown_5b8): -1 toggles it, 0 clears and 1 sets it
// (no change: nothing happens). When repair starts on a damaged building of
// a player-controlled owner, slot 79(7) runs and EVA says "EVA_Repairing";
// the toggle sound (the rules' +0x620 for a building at full strength, +0x62C
// otherwise) plays at the building for such an owner.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@H@Z=00713e60
// @ref ?Unknown_00715B40@@YIXPBDHH@Z=00715b40
// @ref ??_C@_0O@MHGH@EVA_Repairing?$AA@=007cf894

// EVA speech by name (0x00715B40; hypothesis: VoxClass::Speak).
void __fastcall Unknown_00715B40(char const *name, int arg2, int arg3);

void BuildingClass::unknown_slot97(int mode)
{
    switch (mode) {
    case -1:
        unknown_5b8 = !unknown_5b8;
        break;
    case 0:
        if (!unknown_5b8) {
            return;
        }
        unknown_5b8 = false;
        break;
    case 1:
        if (unknown_5b8) {
            return;
        }
        unknown_5b8 = true;
        break;
    }
    int sound;
    if (unknown_5b8) {
        if (Strength == Type->MaxStrength) {
            sound = Rules->unknown_620;
        } else {
            sound = Rules->unknown_62c;
            if (House->Unknown_004F52B0()) {
                unknown_slot79(7);
            }
            unknown_5ae = true;
            if (House->Unknown_004F52B0()) {
                Unknown_00715B40("EVA_Repairing", -1, -1);
            }
        }
    } else {
        sound = Rules->unknown_62c;
    }
    if (House->Unknown_004F52B0()) {
        Unknown_00713E60(sound, CoordStruct(Coord), 0);
    }
}
