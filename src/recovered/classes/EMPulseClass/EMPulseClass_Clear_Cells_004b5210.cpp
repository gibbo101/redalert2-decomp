#include "shared/unknown_globals.hpp"
#include "shared/vector_class.hpp"
#include "shared/abstract.hpp"
#include "shared/empulse_class.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// Use existing canonical map declarations; no map-header proposal.
// @ref ?Map@@=008324e0
// @ref ?Has_Cell@MapClass@@=005480b0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070

void EMPulseClass::Clear_Cells_004B5210()
{
    int y = -Radius;
    int radiusSquared = Radius * Radius;
    for (; y <= Radius; ++y) {
        for (int x = -Radius; x <= Radius; ++x) {
            Cell cell;
            cell = Cell((short)(Position.X + x), (short)(Position.Y + y));
            if (cell.X >= 0 && cell.X < 512 && cell.Y >= 0 && cell.Y < 512 && Map.Has_Cell(cell)) {
                int dx = cell.X - Position.X;
                int dy = cell.Y - Position.Y;
                if (dy * dy + dx * dx <= radiusSquared) {
                    CellClass *mapCell = &Map[cell];
                    mapCell->unknown_140 &= 0xfff7ffffU;
                }
            }
        }
    }
}
