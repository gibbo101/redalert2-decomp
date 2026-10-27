// int TechnoClass::unknown_6c6350(Cell const *cell) (0x006C6350)
// How much a computer-owned techno wants to shoot the wall in cell
// (TechnoClass slot 219): 0 for a human owner, a difficulty without
// DestroyWalls, a cell without a wall overlay, a cell out of range of the
// weapon chosen for it, a weapon without a Wall warhead, a projectile not
// AG, or a wall owned by an ally; otherwise slot 85 less the distance to
// the cell's centre.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int TechnoClass::unknown_6c6350(Cell const *cell)
{
    if (House->Unknown_004F52F0()) {
        return 0;
    }
    if (!Rules->Diff[House->unknown_c8].DestroyWalls) {
        return 0;
    }
    UnknownCellClass *wall = (UnknownCellClass *)&Map[*cell];
    if (wall->unknown_44 == -1 || !unknown_overlay_types_a35de8[wall->unknown_44]->unknown_278) {
        return 0;
    }
    int weapon = unknown_slot174((AbstractClass *)&Map[*cell]);
    if (!unknown_slot84(CoordStruct(cell->X * 256 + 128, cell->Y * 256 + 128, 0), weapon)) {
        return 0;
    }
    WeaponStruct *primary = unknown_slot230();
    if (primary == 0 || primary->WeaponType == 0) {
        return 0;
    }
    WarheadTypeClass *warhead = primary->WeaponType->Warhead;
    if (warhead == 0) {
        return 0;
    }
    if (primary->WeaponType->Projectile != 0 && !primary->WeaponType->Projectile->AG) {
        return 0;
    }
    if (!warhead->Wall || wall->unknown_50 == -1 || House->Is_Ally(Houses[wall->unknown_50])) {
        return 0;
    }
    int distance = Offset_Length(Center_Coord() - CoordStruct(cell->X * 256 + 128, cell->Y * 256 + 128, 0));
    return unknown_slot85(0) - distance;
}
