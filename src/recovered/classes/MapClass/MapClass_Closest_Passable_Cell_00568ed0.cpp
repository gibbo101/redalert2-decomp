// Cell MapClass::Unknown_00568ED0(Cell const &cell, Cell const &from) (0x00568ED0)
// The cell of the isometric tile under `cell` that is closest to `from`
// (TibSun Closest_Passable_Cell): every cell of the tile's grid that has an
// image and lies in the local view (0x0055A660) is measured with Fast_Sqrt;
// the cell itself when it has no tile type.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/fast_math.hpp"
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0

Cell MapClass::Unknown_00568ED0(Cell const &cell, Cell const &from)
{
    Cell best_cell = unknown_cell_a6f238;
    double best_dist = 10000.0;
    CellClass *cptr = &Map[cell];

    if (cptr->IsoTileIndex < 0) {
        return cell;
    }

    IsometricTileTypeClass *iptr = IsoTileTypes[cptr->IsoTileIndex];
    IsoTileImageStruct *image = (IsoTileImageStruct *)iptr->unknown_slot39();

    int w = iptr->unknown_2b4;
    int h = iptr->unknown_2b8;
    int s = (unsigned char)cptr->unknown_11a;

    Cell d = cell - Cell(s % w, s / w);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Cell here = d + Cell(x, y);
            if (image->Tiles[x + y * iptr->unknown_2b4] != 0 && Unknown_0055A660(here, true)) {
                int xdiff = here.X - from.X;
                int ydiff = here.Y - from.Y;
                double dist = Fast_Sqrt(double(xdiff * xdiff + ydiff * ydiff));
                if (dist < best_dist) {
                    best_dist = dist;
                    best_cell = here;
                }
            }
        }
    }

    return best_cell;
}
