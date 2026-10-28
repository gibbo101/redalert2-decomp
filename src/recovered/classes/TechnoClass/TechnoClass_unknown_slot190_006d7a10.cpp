// bool TechnoClass::unknown_slot190(int *out_kind) (0x006D7A10, slot 190)
// Whether the object shows on the radar (hypothesis): never for Invisible
// types or while +0x325 is set, always for RadarVisible types; a player-
// controlled object by +0x373. Otherwise visible unless it is hidden in some
// way (a tunnel under shroud, +0x1B8 == 2, low slot 108 value, the rank's
// ability 11, a hidden map position), in which case slot 191 decides and an
// enemy's blip kind is written: 2 below -20, else 1.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/id_source.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_005683C0@MapClass@@QAE_NABUCoordStruct@@@Z=005683c0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool TechnoClass::unknown_slot190(int *out_kind)
{
    TechnoTypeClass *type = unknown_slot32();
    if (type->Invisible || unknown_325) {
        return false;
    }
    if (type->RadarVisible) {
        return true;
    }
    if (House->Unknown_004F52B0()) {
        return unknown_373 ? true : false;
    }
    int value = unknown_slot108();
    bool ability = unknown_6d7910(11);
    bool hidden = Map.Unknown_00568140(CoordStruct(Coord)) && unknown_b263d8 != 0;
    bool tunnel = (unknown_id_source_a3d290->unknown_000 & 0x1000) && Map.Unknown_005683C0(CoordStruct(Coord));
    if (!tunnel && unknown_1b8 != 2 && value >= -20 && !ability && !hidden) {
        return true;
    }
    if (!unknown_slot191()) {
        return false;
    }
    if (!unknown_player_a35db4->Is_Ally(House) && !ability && !tunnel && !hidden) {
        *out_kind = value < -20 ? 2 : 1;
    }
    return true;
}
