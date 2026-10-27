// Schedules and plays idle infantry/cow actions (0x00503E00).
// Full independent extent includes the ten-entry switch table: 800 bytes.
#include "shared/infantry.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_func_5d27d0@ObjectClass@@QBE_NPBD@Z=005d27d0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@H@Z=00713e60
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?unknown_invalid_coord_a410f8@@3UCoordStruct@@A=00a410f8
// @ref __real@8@3fe08000000200000000=0079c280
// @ref __real@8@4007e100000000000000=0079e6d0
// @ref __real@8@4009e100000000000000=0079d140
// @ref ??_C@_03FEGA@COW?$AA@=007daf04
inline double Infantry_Idle_Interval(double low, double high)
{
    int draw = unknown_id_source_a3d290->Random()(0, 0x7ffffffe);
    return (high - low) * ((double)draw * (1.0 / 2147483646.0)) + low;
}
inline bool Infantry_Play_Idle_Action(InfantryClass *infantry)
{
    int action = unknown_id_source_a3d290->Random()(0, 10);
    bool is_cow = infantry->unknown_func_5d27d0("COW");
    if (is_cow && unknown_id_source_a3d290->Random()(0, 10) < 5) {
        action = 8;
    }
    switch (action) {
    case 3: case 4: case 5:
        infantry->unknown_slot311(9, false, false);
        return true;
    case 6: {
        UnknownFacingDir facing((unsigned short)(unknown_id_source_a3d290->Random()(0,7)<<13));
        infantry->unknown_2e0.Set_Current(UnknownFacingDir((unsigned short)(Dir_To_256(facing) << 8)));
        return true;
    }
    case 1: case 2: case 7:
        infantry->unknown_slot311(10, false, false);
        if (!infantry->unknown_77 && infantry->House->Unknown_004F52B0() && infantry->Type->VoiceComment.Count() > 0
            && unknown_random_839218(0, 2) == 0) {
            CoordStruct coord = infantry->Coord;
            Unknown_00713E60(infantry->Type->VoiceComment[0], coord, 0);
            return true;
        }
        break;
    case 8: {
        UnknownFacingDir facing((unsigned short)(unknown_id_source_a3d290->Random()(0,7)<<13));
        infantry->unknown_2e0.Set_Current(UnknownFacingDir((unsigned short)(Dir_To_256(facing) << 8)));
        if (is_cow || (!infantry->House->Unknown_004F52F0() && infantry->Type->Fraidycat)) {
            infantry->unknown_slot87(unknown_invalid_coord_a410f8, true, false);
            return true;
        }
        break;
    }
    case 9: case 10: {
        UnknownFacingDir facing((unsigned short)(unknown_id_source_a3d290->Random()(0,7)<<13));
        infantry->unknown_2e0.Set_Current(UnknownFacingDir((unsigned short)(Dir_To_256(facing) << 8)));
        break;
    }
    }
    return true;
}
bool InfantryClass::unknown_slot258()
{
    if (unknown_slot257()) {
        // Rules +0x1378 is read as a double; the current shared header pads it.
        unknown_130 = CDTimerClass<FrameTimerClass>((long)Infantry_Idle_Interval(
            Rules->IdleActionFrequency * 450.0,
            Rules->IdleActionFrequency * 1800.0));
        if (Type->Fraidycat && !House->Unknown_004F52F0() && unknown_5bc > 50) {
            unknown_slot87(unknown_invalid_coord_a410f8, true, false);
            return true;
        }
        return Infantry_Play_Idle_Action(this);
    }
    return false;
}
