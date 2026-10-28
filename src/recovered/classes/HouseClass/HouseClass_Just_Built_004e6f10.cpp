// void HouseClass::Just_Built(TechnoClass *techno) (0x004E6F10)
// Records the type an object just built (+0x1B4..+0x1C0 by kind), counts it
// (+0x54A0..+0x54D0) and plays the Rules creation sound of its kind (the
// type's CreateSound overrides it) at the object (TS name).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
// @ref ?Increment@UnknownHouseCounter@@QAEXH@Z=00491c50
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

void HouseClass::Just_Built(TechnoClass *techno)
{
    int sound = -1;
    unknown_18d = true;
    TechnoTypeClass *type = techno->unknown_slot32();
    switch (techno->Kind_Of()) {
    case 1:
        unknown_1bc = type->unknown_slot16();
        unknown_54b0.Increment(type->unknown_slot16());
        sound = Rules->CreateUnitSound;
        break;
    case 15:
        unknown_1b8 = type->unknown_slot16();
        unknown_54c0.Increment(type->unknown_slot16());
        sound = Rules->CreateInfantrySound;
        break;
    case 6:
        unknown_1b4 = type->unknown_slot16();
        unknown_54a0.Increment(type->unknown_slot16());
        break;
    case 2:
        unknown_1c0 = type->unknown_slot16();
        unknown_54d0.Increment(type->unknown_slot16());
        sound = Rules->CreateAircraftSound;
        break;
    }
    if (type->CreateSound != -1) {
        sound = type->CreateSound;
    }
    if (sound != -1) {
        CoordStruct coord = techno->Coord;
        Voc_Play_At(sound, coord, 0);
    }
    unknown_144 = true;
}
