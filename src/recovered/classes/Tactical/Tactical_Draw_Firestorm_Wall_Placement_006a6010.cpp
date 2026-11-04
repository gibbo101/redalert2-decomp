// void Tactical::Draw_Firestorm_Wall_Placement(bool drawtrans, Cell cell) (0x006A6010): from the pending firestorm
// wall's cell, walks each of the four directions while the cells are clear to build, up to the wall's guard range; when
// the run ends at a player's firestorm wall, draws the placement shape over every cell walked (TibSun
// Tactical::Draw_Firestorm_Wall_Placement).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/palette.hpp"
#include "shared/gadget.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?TransIconset@DisplayClass@@2PBXB=00852614
// @ref ?unknown_4718b0@CellClass@@QAE_NHHH@Z=004718b0

void Tactical::Draw_Firestorm_Wall_Placement(bool drawtrans, Cell cell)
{
    for (int index = 0; index < 8; index += 2) {
        Cell scan = cell;
        int count = 0;
        BuildingTypeClass *type = ((BuildingClass *)Map.unknown_11a0)->Type;
        int range = type->GuardRange.Value >> 8;
        int facing = index;
        bool found = false;
        for (; count < range; count++) {
            scan = Adjacent_Cell(scan, facing);
            BuildingClass *building = (BuildingClass *)Map[scan].unknown_4717b0();
            if (building != 0 && building->Type->FirestormWall && building->House->Unknown_004F52B0()) {
                found = true;
                break;
            }
            if (!Map[scan].unknown_4718b0(type->SpeedType, (int)type, (int)unknown_player_a35db4)) {
                break;
            }
        }

        if (found && count > 0) {
            int flags = drawtrans ? 0x10606 : 0x20606;
            Cell drawcell = Adjacent_Cell(cell, facing);
            for (int i = 0; i < count; i++) {
                int height = 15 * Map[drawcell].unknown_11b;
                int zheight = 15 * Map[drawcell].unknown_11b;
                Point2D offset(0, -1 - height);
                int zoff = -2 - zheight;
                CoordStruct coord = Coord_Snap(Cell_Center(drawcell));
                Point2D pixel;
                Coord_To_Pixel(coord, pixel);
                pixel.X -= 30;
                int px = pixel.X + 30;
                int py = offset.Y + pixel.Y;
                Point2D point(px, py);
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, (ShapeFileStruct const *)DisplayClass::TransIconset, 0, point,
                    unknown_rect_839630, flags, 0, zoff, 0, 1000, 0, 0, Point2D(0, 0));
                drawcell = Adjacent_Cell(drawcell, facing);
            }
        }
    }
}
