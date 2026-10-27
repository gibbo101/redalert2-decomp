// Damage eligible cell occupants, then wall/chain-reaction overlays and terrain.
// @ref ?unknown_47bb10@CellClass@@QBE_NXZ=0047bb10
#include "shared/wave.hpp"
#include "shared/cell.hpp"
#include "shared/weapon_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_475fe0@CellClass@@QAEHH@Z=00475fe0
// @ref ?Unknown_00562F50@MapClass@@QAEXPAVCellClass@@@Z=00562f50
// @ref ?unknown_47e2b0@Cell@@QAEXXZ=0047e2b0
void WaveClass::Damage_Cell_00721eb0(CoordStruct const &coord)
{
    if (Owner) {
        Cell location = Coord_Cell(coord);
        CellClass &cell = Map[location];
        WeaponTypeClass *weapon = Owner->unknown_slot231(0)->WeaponType;
        WarheadTypeClass *warhead = weapon->Warhead;
        int damage = weapon->unknown_98;
        ObjectClass *object;
        if (!(cell.unknown_140 & 0x100) || unknown_a0.Z < (cell.unknown_11b + 4) * unknown_geometry_g)
            object = cell.OccupierPtr;
        else object = cell.AltOccupierPtr;
        for (; object; object = object->unknown_30) {
            if (object != Owner && object->unknown_7d && object->unknown_74 && !object->unknown_76 && object->Strength > 0)
                object->unknown_slot86(&damage, 0, warhead, Owner, false, 0);
        }
        if (cell.OverlayIndex != -1) {
            OverlayTypeClass *overlay = (OverlayTypeClass *)unknown_overlay_types_a35de8[cell.OverlayIndex];
            if (overlay->ChainReaction) {
                location = cell.MapCoords;
                location.unknown_47e2b0();
            }
            if (overlay->Wall) cell.unknown_475fe0(weapon->unknown_98);
        }
        if (cell.unknown_47bb10()) {
            int chance = Rules->unknown_140c;
            if (unknown_id_source_a3d290->Random()(0, 99) < chance) Map.Unknown_00562F50(&cell);
        }
    }
}
