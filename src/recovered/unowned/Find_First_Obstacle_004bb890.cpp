// CellClass *Find_First_Obstacle_004bb890(...) (0x004BB890): walks the line from one coordinate to another one
// cell step at a time and returns the first cell that blocks the projectile type (a cliff rise or a wall when the
// type is subject to them, Get_Obstacle_004bbaf0), or null (names after Ares' hypotheses).
// The difference is taken through a rebuilt copy of `from` and member-wise stores Y, X, Z: that order loads the
// source Y first and keeps the loop's running Z sum in the original register order.
#ifndef RA2_COORD_TIMES
#define RA2_COORD_TIMES
#endif
#include "shared/cell_class.hpp"
#include "shared/bullet_type.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Get_Obstacle_004bbaf0@@YIPAVCellClass@@PAV1@00UCoordStruct@@PBVBulletTypeClass@@PBVHouseClass@@@Z=004bbaf0

CellClass *__fastcall Get_Obstacle_004bbaf0(CellClass *source, CellClass *target, CellClass *last,
    CoordStruct coord, BulletTypeClass const *type, HouseClass const *house);

CellClass *__fastcall Find_First_Obstacle_004bb890(CoordStruct const &from, CoordStruct const &to,
    BulletTypeClass const *type, HouseClass const *house)
{
    if (type->SubjectToCliffs || type->SubjectToWalls) {
        Cell fromcell(from);
        Cell tocell(to);
        int xdelta = abs(fromcell.X - tocell.X);
        int ydelta = abs(fromcell.Y - tocell.Y);
        int steps = xdelta > ydelta ? xdelta : ydelta;
        CoordStruct start = CoordStruct(from.X, from.Y, from.Z);
        CoordStruct delta;
        delta.Y = to.Y - start.Y;
        delta.X = to.X - start.X;
        delta.Z = to.Z - start.Z;
        CoordStruct step = delta / steps;
        CellClass *source = &Map[fromcell];
        CellClass *target = &Map[tocell];
        CellClass *cell = source;
        for (int i = 0; i < steps; i++) {
            CoordStruct coord = from + step * i;
            CellClass *obstacle = Get_Obstacle_004bbaf0(source, target, cell, coord, type, house);
            if (obstacle != 0) {
                return obstacle;
            }
            cell = &Map[Cell(coord)];
        }
    }
    return 0;
}
