// CellClass *Find_First_Impenetrable_Obstacle_004bbaa0(...) (0x004BBAA0): the first cell on the line from
// one coordinate to another that blocks a weapon's projectile (Find_First_Obstacle_004bb890), unless the weapon's
// warhead destroys walls and the cell holds a wall or gate (names after Ares' hypotheses).
#include "shared/cell_class.hpp"
#include "shared/weapon_type.hpp"
#include "shared/house.hpp"
// @ref ?Find_First_Obstacle_004bb890@@YIPAVCellClass@@ABUCoordStruct@@0PBVBulletTypeClass@@PBVHouseClass@@@Z=004bb890

CellClass *__fastcall Find_First_Obstacle_004bb890(CoordStruct const &from, CoordStruct const &to,
    BulletTypeClass const *type, HouseClass const *house);

CellClass *__fastcall Find_First_Impenetrable_Obstacle_004bbaa0(CoordStruct const &from, CoordStruct const &to,
    WeaponTypeClass const *weapon, HouseClass const *house)
{
    BulletTypeClass const *type = weapon->Projectile;
    CellClass *cell = Find_First_Obstacle_004bb890(from, to, type, house);
    if (cell != 0 && cell->unknown_475840(-1, -1) && weapon->Warhead->Wall) {
        return 0;
    }
    return cell;
}
