// void BombClass::Unknown_00435D30() (0x00435D30): sets the bomb off at once. Unless it sits on nothing or is
// spent, the target loses the bomb; a target with +0x76 set only marks the bomb spent; otherwise the Ivan
// explosion hits the target's coordinate (IvanDamage/IvanWarhead from the planting unit) with its damage
// animation, and a bridge repair hut target makes the map destroy the bridge by it (0x00557090 when a cell within
// two holds a bridge tile or a bridge overlay 0x4A-0x65, else 0x00556520). Then it lets go of its owner, target,
// house and sound. Map's 0x00556520/0x00557090 declarations are guarded by RA2_MAP_BOMB_BRIDGE (set by the unit's
// header-statics source).
#include "shared/object.hpp"
#include "shared/anim.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/building_class.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0047FCC0@@YGHUCoordStruct@@@Z=0047fcc0
// @ref ?Unknown_0047E2C0@@YIXABUCoordStruct@@HHPAVWarheadTypeClass@@H@Z=0047e2c0
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
// @ref ?Unknown_00556520@MapClass@@QAEXABVCell@@@Z=00556520
// @ref ?Unknown_00557090@MapClass@@QAEXABVCell@@@Z=00557090

// The land type of the cell under coord.
static inline int Land_At(CoordStruct const &coord)
{
    return Map[Cell(coord)].unknown_ec;
}

void BombClass::Unknown_00435D30()
{
    if (Target == 0 || unknown_58) {
        return;
    }
    bool flag = Target->unknown_76;
    Target->unknown_38 = 0;
    if (flag) {
        Target->unknown_68 = false;
        unknown_58 = true;
    } else {
        Target->unknown_68 = false;
        unknown_58 = true;
        CoordStruct coord = Target->Coord;
        Unknown_0047E2C0(coord, Rules->IvanDamage, (int)Owner, Rules->IvanWarhead, 1);
        new AnimClass(Select_Damage_Anim(Rules->IvanDamage, Rules->IvanWarhead, Land_At(coord), &coord),
            coord, 0, 1, 0x2600, Unknown_0047FCC0(coord));
        if (Target != 0 && Target->Kind_Of() == 6 && ((BuildingClass *)Target)->Type->BridgeRepairHut) {
            bool bridge = false;
            for (int y = -2; y < 3; y++) {
                for (int x = -2; x < 3; x++) {
                    int tile = Map[Target->unknown_slot104() + Cell(x, y)].IsoTileIndex;
                    int overlay = Map[Target->unknown_slot104() + Cell(x, y)].OverlayIndex;
                    if ((tile >= unknown_tileset_a6cb68 && tile < unknown_tileset_a6cb68 + 16) || (overlay >= 0x4A && overlay <= 0x65)) {
                        bridge = true;
                    }
                }
            }
            if (bridge) {
                Map.Unknown_00557090(Target->unknown_slot104());
            } else {
                Map.Unknown_00556520(Target->unknown_slot104());
            }
        }
    }
    Owner = 0;
    Target = 0;
    unknown_28 = 0;
    unknown_3c.Unknown_00405FE0();
    unknown_54 = 0;
}
