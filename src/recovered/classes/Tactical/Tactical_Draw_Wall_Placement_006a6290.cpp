// void Tactical::Draw_Wall_Placement(bool drawtrans, Cell cell) (0x006A6290): when the pending building builds a wall
// overlay, walks each of the four directions from its cell while the cells are clear to build, up to its guard range;
// when the run ends at the player's own wall overlay of that type, draws the placement shape over every cell walked
// (TibSun Tactical::Draw_Wall_Placement).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/palette.hpp"
#include "shared/gadget.hpp"
#include "shared/building_type_class.hpp"
#include "shared/overlay_type.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?TransIconset@DisplayClass@@2PBXB=00852614
// @ref ?unknown_4718b0@CellClass@@QAE_NHHH@Z=004718b0

void Tactical::Draw_Wall_Placement(bool drawtrans, Cell cell)
{
    OverlayTypeClass const *to_overlay = ((BuildingClass *)Map.unknown_11a0)->Type->ToOverlay;
    if (to_overlay == 0) {
        return;
    }

    for (int index = 0; index < 8; index += 2) {
        Cell scan = cell;
        int count = 0;
        BuildingTypeClass *type = ((BuildingClass *)Map.unknown_11a0)->Type;
        int range = type->GuardRange.Value >> 8;
        if (range <= 0) {
            continue;
        }
        bool found = false;
        for (; count < range; count++) {
            scan = Adjacent_Cell(scan, index);
            CellClass *cellptr = &Map[scan];
            if (cellptr->OverlayIndex != -1 && to_overlay->ArrayIndex == cellptr->OverlayIndex && unknown_player_a35db4->ArrayIndex == Map[scan].unknown_50) {
                found = true;
                break;
            }
            if (!Map[scan].unknown_4718b0(type->SpeedType, (int)type, (int)unknown_player_a35db4)) {
                break;
            }
        }

        if (found && count > 0) {
            int flags = drawtrans ? 0x10606 : 0x20606;
            Cell drawcell = cell;
            drawcell = Adjacent_Cell(drawcell, index);
            for (int i = 0; i < count; i++) {
                int height = 15 * Map[drawcell].unknown_11b;
                int zoff = 15 * Map[drawcell].unknown_11b;
                Point2D offset(0, -1 - height);
                zoff = -2 - zoff;
                CoordStruct coord = Coord_Snap(Cell_Center(drawcell));
                Point2D pixel;
                Coord_To_Pixel(coord, pixel);
                pixel.X -= 30;
                Point2D point;
                point.X = pixel.X + 30;
                point.Y = pixel.Y + offset.Y;
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, (ShapeFileStruct const *)DisplayClass::TransIconset, 0, point,
                    unknown_rect_839630, flags, 0, zoff, 0, 1000, 0, 0, Point2D(0, 0));
                drawcell = Adjacent_Cell(drawcell, index);
            }
        }
    }
}
