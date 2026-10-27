// int UnitClass::unknown_slot27(Cell const *where, bool arg2, bool arg3) (0x007041F0, slot 27)
// The action for a cell (hypothesis: What_Action): arg1 points at the
// cell, arg2 asks to look through the fog. Only for player-controlled
// units. Starts from the foot's answer (an unarmed unit's 5 becomes 59);
// on a visible cell a harvester answers 6 for tiberium land or fogged
// tiberium overlay, a weeder 6 for vein land or fogged veins (overlay
// 0x7E, data >= 0x30); actions 1 then give 0x23/0x24 for cells with
// 0x00479CC0 and 0 for units with +0x5C8; an action 5 the unit cannot
// take (slot 185) becomes 0.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/fogged_object.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_slot27@FootClass@@UAEHPBVCell@@_N1@Z=004cc650
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?unknown_bridge_height_ad057c@@3HA=00ad057c
// @ref ?unknown_479cc0@CellClass@@QBE_NXZ=00479cc0
// @ref ?unknown_47a120@CellClass@@QBE_NPAVTechnoClass@@@Z=0047a120

class OverlayTypeClass;
extern DynamicVectorClass<OverlayTypeClass *> OverlayTypes;
// An overlay type's tiberium flag (a view until shared/overlay_type.hpp is
// installed).
struct UnknownUnitOverlayTypeView {
    char unknown_000[0x279];
    bool Tiberium;                          // +0x279
};
// The height a bridge adds (0x00AD057C).
extern int unknown_bridge_height_ad057c;

int UnitClass::unknown_slot27(Cell const *where, bool arg2, bool arg3)
{
    if (!House->Unknown_004F52B0()) {
        return 0;
    }
    CellClass *cell = &Map[*where];
    int action = FootClass::unknown_slot27(where, arg2, arg3);
    if (unknown_6c16f0(-1) < 0 && House->Unknown_004F52B0() && action == 5) {
        action = 59;
    }
    int overlay = -1;
    if (arg2 && (unknown_id_source_a3d290->unknown_000 & 0x1000) && cell->FoggedObjects) {
        for (int index = 0; index < cell->FoggedObjects->Count(); index++) {
            FoggedObjectClass *fogged = (*cell->FoggedObjects)[index];
            if (fogged->unknown_74 && fogged->unknown_30 == 20) {
                overlay = fogged->unknown_24;
            }
        }
    }
    CoordStruct coord(where->X * 256 + 128, where->Y * 256 + 128, 0);
    coord.Z = Map.Unknown_0055A280(coord);
    if (Map[coord].unknown_140 & 0x100) {
        coord.Z += unknown_bridge_height_ad057c;
    }
    if (!Map.Unknown_00568140(coord)) {
        if (action == 1) {
            if ((cell->unknown_ec == 5 || overlay != -1
                    && ((UnknownUnitOverlayTypeView *)OverlayTypes[overlay])->Tiberium && arg2)
                && Type->Harvester) {
                return 6;
            }
            if ((cell->unknown_ec == 11 || overlay == 0x7E && cell->OverlayData >= 0x30 && arg2)
                && Type->Weeder) {
                return 6;
            }
            goto move;
        }
    } else if (action == 1) {
        goto move;
    }
    if (action == 5 && !unknown_slot185()) {
        action = 0;
    }
    return action;
move:
    if (Map[*where].unknown_479cc0()) {
        return Map[*where].unknown_47a120(this) ? 0x23 : 0x24;
    }
    if (unknown_5c8) {
        action = 0;
    }
    return action;
}
