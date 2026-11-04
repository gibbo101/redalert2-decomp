// Rect CellClass::unknown_4752b0() const (0x004752B0): Westwood's Cell_Render_Rect: the
// screen rectangle of the cell's tile, taller by its extra image.
#include "shared/cell.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BK@LJGH@Invalid?5tile?5at?5?$CI?$CFd?0?5?$CFd?$CJ?6?$AA@=007d2c84

Rect CellClass::unknown_4752b0() const
{
    Point2D point;
    unknown_tactical_83996c->Coord_To_Pixel(Coord_Snap(Cell_Coord(MapCoords)), point);
    point.X -= 30;
    point.Y += unknown_int_839634 - 15 * unknown_11b;

    Rect rect;
    rect.X = point.X;
    rect.Y = point.Y;
    rect.Width = 60;
    rect.Height = 30;

    if (IsoTileIndex == 0xFFFF) {
        return rect;
    }

    if (IsoTileIndex >= 0 && IsoTileIndex < IsoTileTypes.Count()) {
        IsometricTileTypeClass *itype = IsoTileTypes[IsoTileIndex];
        int subtile = (unsigned char)unknown_11a;
        IsoTileImageStruct const *image = (IsoTileImageStruct const *)itype->unknown_slot39();
        if (image == 0) {
            return Rect();
        }
        subtile = subtile < image->unknown_00[0] * image->unknown_00[1] - 1 ? subtile : image->unknown_00[0] * image->unknown_00[1] - 1;
        IsoTileCellStruct const *tile = (IsoTileCellStruct const *)image->Tiles[subtile];
        if (tile->IsHasExtraData) {
            int dy = tile->Y - tile->ExtraY;
            dy = dy < 0 ? 0 : dy;
            rect.Y -= dy;
            rect.Height += dy;
        }
        return rect;
    } else {
        Debug_Printf("Invalid tile at (%d, %d)\n", MapCoords.X, MapCoords.Y);
        return rect;
    }
}
