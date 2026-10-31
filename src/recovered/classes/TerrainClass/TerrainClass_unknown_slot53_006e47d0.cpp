// bool TerrainClass::unknown_slot53(CoordStruct const *coord, int dir) (0x006E47D0)
// Places the terrain object (ObjectClass slot 53). On success every
// neighbouring cell counts one more adjacent terrain object (+0x122), the
// screen position of the object is stored (offset by the view's position)
// and a tiberium-spawning type clears the overlay of its cell.
#include "shared/terrain.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_slot42@ObjectClass@@UBE?AUCoordStruct@@XZ=0041b270

bool TerrainClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    if (ObjectClass::unknown_slot53(coord, dir)) {
        Cell cell(coord->X / 256, coord->Y / 256);
        for (int facing = 0; facing < 8; facing++) {
            CellClass &next = Map[cell + AdjacentCell[facing & 7]];
            next.unknown_122++;
        }
        Point2D &pixel = (Point2D &)unknown_b8.Width;
        unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(), pixel);
        Point2D offset = unknown_tactical_83996c->unknown_b0;
        pixel.X += offset.X;
        pixel.Y += offset.Y;
        if (Class->SpawnsTiberium) {
            Map[*coord].OverlayIndex = -1;
            Map[*coord].OverlayData = 0;
        }
        return true;
    }
    return false;
}
