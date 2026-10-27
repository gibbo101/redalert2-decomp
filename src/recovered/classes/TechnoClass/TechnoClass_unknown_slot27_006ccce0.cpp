// int TechnoClass::unknown_slot27(Cell const *cell, bool arg2, bool arg3) (0x006CCCE0, slot 27)
// The action for a cell (Westwood's What_Action for a cell). Without arg3,
// the force-fire and force-move key pairs and the 0x00A40BA4/0x00A40BA8 pair
// are read; force fire and force
// move together cancel both. Slots 111/112 refuse (0). For a human-
// controlled owner: force fire with the third key (or +0x388) on a slot 39
// object answers 0x33 (or 0x1A without a waypoint in the cell); an armed
// object attacks (5) a cell its weapon can hit when forced, when the cell's
// overlay (or, with the 0x1000 scenario flag and arg2, a cell entry's) is
// attackable, when the cell burns, or when an enemy wall/parasite case
// allows it; then movement: 1 (move) or 2 (no move).
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/keyboard.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Down@WWKeyboardClass@@QAE_NG@Z=00532890
// @ref ?unknown_key_a40ba4@@3HA=00a40ba4
// @ref ?unknown_key_a40ba8@@3HA=00a40ba8
// @ref ?KeyForceFire1@@3HA=00a40bac
// @ref ?KeyForceFire2@@3HA=00a40bb0
// @ref ?KeyForceMove1@@3HA=00a40bb4
// @ref ?KeyForceMove2@@3HA=00a40bb8
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Unknown_004C2030@@YIPAUUnknownCellEntryType@@PAUUnknownCellEntry28@@@Z=004c2030
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_func_4ed200@HouseClass@@QAEPAUWaypointClass@@ABVCell@@@Z=004ed200
// @ref ?Unknown_0047BB10@UnknownCellClass@@QAE_NXZ=0047bb10
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Unknown_00710160@@YIPAUUnknownCellObject710160@@ABVCell@@@Z=00710160

// A key binding is down (the bindings are ints; WWKeyboardClass takes 16-bit keys).
inline bool Techno_Key_Down(int key) { return WWKeyboard->Down(key); }

int TechnoClass::unknown_slot27(Cell const *cell, bool arg2, bool arg3)
{
    UnknownCellClass *cellptr = Map_Cell_At(*cell);
    UnknownOverlayType *overlay = 0;
    bool force_fire = !arg3 && (Techno_Key_Down(KeyForceFire1) || Techno_Key_Down(KeyForceFire2));
    bool force_move = !arg3 && (Techno_Key_Down(KeyForceMove1) || Techno_Key_Down(KeyForceMove2));
    bool third = !arg3 && (Techno_Key_Down(unknown_key_a40ba4) || Techno_Key_Down(unknown_key_a40ba8));
    if (force_move && force_fire) {
        force_move = false;
        force_fire = false;
    }
    int overlay_index = -1;
    bool entry_target = false;
    if (unknown_slot111() || unknown_slot112()) {
        return 0;
    }
    if ((unknown_id_source_a3d290->unknown_000 & 0x1000) && arg2 && cellptr->unknown_28 != 0) {
        for (int index = 0; index < cellptr->unknown_28->Count(); index++) {
            UnknownCellEntry28 *entry = (*cellptr->unknown_28)[index];
            if (entry->unknown_74) {
                if (entry->unknown_30 == 0x14) {
                    overlay_index = entry->unknown_24;
                } else if (entry->unknown_30 == 6
                    && (entry->unknown_28 == 0 || !unknown_player_a35db4->Is_Ally(entry->unknown_28))
                    && (Unknown_004C2030(entry) == 0 || Unknown_004C2030(entry)->unknown_201)) {
                    entry_target = true;
                }
            }
        }
    }
    if (overlay_index != -1) {
        overlay = unknown_overlay_types_a35de8[overlay_index];
    } else if (cellptr->unknown_44 != -1) {
        overlay = unknown_overlay_types_a35de8[cellptr->unknown_44];
    }
    bool can_deploy = unknown_slot193();
    if (House->Unknown_004F52B0() && ((force_fire && third) || unknown_388)
        && unknown_slot39() && (unknown_slot38() || can_deploy)) {
        if (unknown_player_a35db4->unknown_func_4ed200(*cell) == 0 && !unknown_388) {
            return 0x1A;
        }
        return 0x33;
    }
    WeaponStruct *primary;
    if (House->Unknown_004F52B0() && (primary = unknown_slot230()) != 0 && primary->WeaponType != 0) {
        int weapon = unknown_slot174((AbstractClass *)(int)Map_Cell_At(*cell));
        bool burning = (Map_Cell_At(*cell))->Unknown_0047BB10();
        if (burning) {
            WeaponTypeClass *weapon_type = unknown_slot230()->WeaponType;
            if (weapon_type->Warhead->Fire) {
                burning = false;
            }
        }
        if (force_fire || (overlay != 0 && overlay->unknown_201) || burning || entry_target) {
            WarheadTypeClass *warhead = unknown_slot230()->WeaponType->Warhead;
            bool enemy = cellptr->unknown_50 != -1 ? !Houses[cellptr->unknown_50]->Is_Ally(House) : false;
            UnknownCellObject710160 *object = Unknown_00710160(*cell);
            bool occupied = object != 0 && !object->unknown_e8 && object->unknown_6c > 0;
            if (force_fire || overlay == 0 || occupied
                || (enemy && overlay->unknown_278 && (warhead->Wall || (warhead->Wood && overlay->unknown_9c == 6)))) {
                if (unknown_slot39() || unknown_slot84(CoordStruct(cell->X * 256 + 128, cell->Y * 256 + 128, 0), weapon)) {
                    return 5;
                }
            }
        }
        if (unknown_slot208((ObjectClass *)cellptr)
            && (unknown_slot39() || unknown_slot84(CoordStruct(cell->X * 256 + 128, cell->Y * 256 + 128, 0), weapon))) {
            return 5;
        }
    }
    if (House->Unknown_004F52B0() && (unknown_slot39() || unknown_slot153())) {
        if (Map.Unknown_0055A660(*cell, true)) {
            if (force_move) {
                return 1;
            }
            if (unknown_slot153() && third) {
                return 1;
            }
            if (unknown_slot39()) {
                if (unknown_slot101((int)Map_Cell_At(*cell), -1, -1, 0, 1) <= 1 || arg2) {
                    return 1;
                }
                if (unknown_slot32()->unknown_af5
                    && unknown_slot101((int)Map_Cell_At(*cell), -1, -1, 0, 0) <= 1) {
                    return 1;
                }
            }
        }
        return 2;
    }
    return 0;
}
