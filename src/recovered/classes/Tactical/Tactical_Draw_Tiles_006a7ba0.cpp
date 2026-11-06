// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void Tactical::Draw_Tiles(Rect const &area, Rect const &cliprect) (0x006A7BA0)
// Adopted from ra2-decomp Tactical::Draw_Tiles (YR 0x006D7560).
// Draws the tile of every cell of the diagonal band under area whose render
// rectangle is valid and meets area.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?Draw_Tiles@Tactical@@QAEXABVRect@@0@Z=006a7ba0

static inline Point2D Pixel_To_Ground_Point(Matrix3D const &matrix, Point2D const &pixel)
{
    Vector3 ground;
    ground.X = pixel.X;
    ground.Y = pixel.Y;
    ground.Z = 0;
    ground = matrix * ground;
    return Point2D(ground.X, ground.Y);
}

static inline void Project_Tile_Left(Tactical &view, CoordStruct const &coord, Point2D &pixel)
{
    view.Coord_To_Pixel(coord, pixel);
    pixel.X -= 60 / 2;
}

void Tactical::Draw_Tiles(Rect const &area, Rect const &cliprect)
{
    Point2D point = Pixel_To_Ground_Point(unknown_de4, Point2D(area.Top_Left()) + Point2D(TacPixelX, TacPixelY) - unknown_rect_839630.Top_Left());
    CoordStruct lepton(point.X, point.Y, 0);
    Cell origin(lepton.X / 256, lepton.Y / 256);
    Cell base = origin;

    int ycount = area.Height / (30 / 2) + 17;
    int xcount = area.Width / 60 + 4;

    base.X -= 2;
    int ix, iy;
    for (iy = 0; iy < ycount; iy++) {
        Cell step(iy / 2, (iy + 1) / 2);
        Cell cell = base + step;

        for (ix = xcount; ix > 0; ix--) {
            if (Map.Unknown_0054AAB0(cell)) {
                CellClass *cellptr = &Map[cell];
                Rect render = cellptr->unknown_4752b0();
                Rect inter = Intersect(area, render);
                Point2D pixel;
                Project_Tile_Left(*this, Coord_Snap(Cell_Center(cell)), pixel);
                if (render.Is_Valid() && inter.Is_Valid()) {
                    cellptr->Draw_It(pixel, cliprect, 0);
                }
            }
            cell += Cell(1, -1);
        }
    }
}
