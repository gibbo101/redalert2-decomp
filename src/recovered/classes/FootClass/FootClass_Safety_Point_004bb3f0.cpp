// Cell FootClass::Unknown_004BB3F0(Cell const &from, Cell const &to, int start, int max) (0x004BB3F0)
// TibSun Safety_Point (findpath.cpp): walks away from `from` past `to` for each distance
// start..max-1 and scans the side (diagonal) or the corner (straight) of that ring for a cell
// the unit can enter; the zero cell when none.
#include "shared/foot.hpp"
#include "shared/fast_math.hpp"
#include "shared/map_view.hpp"
#include "shared/dir_type.hpp"

#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return AdjacentCell[facing & 7] + cell;
}
#endif

// TibSun DirType::Direction(Cell, Cell) (face.h; its dead `cell1 == cell2` store keeps the 16-bit
// from.X load first), DirType(double) / As_Dir8 and Facing_Sub, as this unit's helpers.
inline DirType Cell_Direction_4bb3f0(Cell const &cell1, Cell const &cell2)
{
    DirType dir;
    if (cell1 == cell2) {
        dir.Facing = 0;
    }
    dir.Facing = (short)((Fast_Atan2((double)(int)cell1.Y - (double)(int)cell2.Y, (double)(int)cell2.X - (double)(int)cell1.X)
        - 1.5707963267948966) * -10430.060040584269);
    return dir;
}
inline FacingType Dir_Facing_4bb3f0(DirType facing)
{
    return (FacingType)(((((unsigned int)facing.Raw >> 12) + 1) >> 1) % 8);
}
inline FacingType Facing_Sub_4bb3f0(int first, int second)
{
    return (FacingType)((first - second) & 7);
}
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

Cell FootClass::Unknown_004BB3F0(Cell const &from, Cell const &to, int start, int max)
{
    int dir = Facing_Sub_4bb3f0(Dir_Facing_4bb3f0(Cell_Direction_4bb3f0(from, to)) ^ 4, 1);

    Cell next;
    int lp;
    for (int dist = start; dist < max; dist++) {
        next = to;
        for (lp = 0; lp < dist; lp++) {
            next = Adjacent_Cell(next, dir);
        }

        if (dir & 1) {
            for (lp = 0; lp < dist << 1; lp++) {
                next = Adjacent_Cell(next, (dir + 3) & 7);
                if (unknown_slot101(&Map[next], (dir + 3) & 7, -1, 0, true) == 0) {
                    return next;
                }
            }
        } else {
            for (lp = 0; lp < dist; lp++) {
                next = Adjacent_Cell(next, (dir + 2) & 7);
                if (unknown_slot101(&Map[next], (dir + 2) & 7, -1, 0, true) == 0) {
                    return next;
                }
            }
            for (lp = 0; lp < dist; lp++) {
                next = Adjacent_Cell(next, (dir + 4) & 7);
                if (unknown_slot101(&Map[next], (dir + 4) & 7, -1, 0, true) == 0) {
                    return next;
                }
            }
        }
    }
    return unknown_geometry_k;
}
