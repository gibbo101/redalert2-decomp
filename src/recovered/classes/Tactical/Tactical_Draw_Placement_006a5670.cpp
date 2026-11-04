// void Tactical::Draw_Placement(bool drawtrans) (0x006A5670): marks the footprint of the object waiting for placement
// and of the secondary cell list, and previews the run of a wall, fence or firestorm post (TibSun Tactical::Draw_Placement).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/mouse.hpp"
#include "shared/building_type_class.hpp"
#include "shared/overlay_type.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Draw_Placement_Cursor@CellClass@@QAE_NABUPoint2D@@ABVRect@@_N@Z=00473f20
// @ref ?Draw_Fence_Placement@Tactical@@QAEX_NVCell@@@Z=006a5d70
// @ref ?Draw_Firestorm_Wall_Placement@Tactical@@QAEX_NVCell@@@Z=006a6010

void Tactical::Draw_Placement(bool drawtrans)
{
    Cell start = Cell(0, 0);
    Cell dims;

    if (Map.unknown_11a4 != 0) {
        Point2D mouse = WWMouse->Get_Mouse_XY();
        if (!unknown_rect_839630.Is_Point_Within(mouse)) {
            return;
        }

        if (Map.unknown_11a4->Kind_Of() == 7 && ((BuildingTypeClass *)Map.unknown_11a4)->Gate) {
            dims = Cell(3, 3);
            start = Cell(-1, -1);
        } else {
            dims = Map.Unknown_00499810(Map.unknown_1178);
        }

        bool all_valid = true;
        for (int cx = start.X; cx < dims.X; cx++) {
            for (int cy = start.Y; cy < dims.Y; cy++) {
                Cell cell = Cell(cx, cy) + Map.unknown_1170 + Map.unknown_1174;
                CoordStruct coord = Coord_Snap(Cell_Center(cell));
                Point2D pixel;
                Coord_To_Pixel(coord, pixel);
                pixel.X = pixel.X - 30;
                if (Map.Unknown_0054AAB0(cell)) {
                    CellClass *cellptr = &Map[cell];
                    all_valid = cellptr->Draw_Placement_Cursor(pixel, unknown_rect_839630, drawtrans) && all_valid;
                }
            }
        }

        int rtti = Map.unknown_11a4->Kind_Of();

        if (unknown_flag_a40d13 && Map.unknown_11a0 != 0) {
            Cell cell = start + Map.unknown_1170 + Map.unknown_1174;
            CoordStruct coord = Cell_Center(cell);
            if (rtti == 7) {
                coord = Coord_Snap(coord);
            }
            coord.Z = Map.Unknown_0055A280(coord);
            Map.unknown_11a0->unknown_slot103(coord);
            Point2D pixel;
            Coord_To_Pixel(coord, pixel);
            if (rtti != 0x12) {
                Map.unknown_11a0->unknown_slot68((int)&pixel, (int)&unknown_rect_839630);
            }
        }

        if (all_valid && Map.unknown_11a0 != 0 && Map.unknown_11a0->Kind_Of() == 6) {
            BuildingClass *bptr = (BuildingClass *)Map.unknown_11a0;
            if (bptr->Type->LaserFencePost) {
                Draw_Fence_Placement(drawtrans, Cell(start.X, start.Y) + Map.unknown_1170 + Map.unknown_1174);
            } else if (bptr->Type->FirestormWall) {
                Draw_Firestorm_Wall_Placement(drawtrans, Cell(start.X, start.Y) + Map.unknown_1170 + Map.unknown_1174);
            } else if (bptr->Type->ToOverlay != 0 && bptr->Type->ToOverlay->Wall) {
                Draw_Wall_Placement(drawtrans, Cell(start.X, start.Y) + Map.unknown_1170 + Map.unknown_1174);
            }
        }
    }

    if (!unknown_flag_a40d13 && Map.unknown_1190 != 0) {
        if (((ObjectTypeClass *)Map.unknown_1190)->Kind_Of() == 7 && ((BuildingTypeClass *)Map.unknown_1190)->Gate) {
            dims = Cell(3, 3);
            start = Cell(-1, -1);
        } else {
            dims = Map.Unknown_00499810(Map.unknown_1188);
        }
        for (int cx = start.X; cx < dims.X; cx++) {
            for (int cy = start.Y; cy < dims.Y; cy++) {
                Cell cell = Cell(cx, cy) + Map.unknown_117e + Map.unknown_1182;
                CoordStruct coord = Coord_Snap(Cell_Center(cell));
                Point2D pixel;
                Coord_To_Pixel(coord, pixel);
                pixel.X = pixel.X - 30;
                if (Map.Unknown_0054AAB0(cell)) {
                    CellClass *cellptr = &Map[cell];
                    cellptr->Draw_Placement_Cursor(pixel, unknown_rect_839630, drawtrans);
                }
            }
        }
    }
}
