// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void Tactical::Unknown_006AADD0(CellClass *cell) (0x006AADD0)
// Adopted from ra2-decomp Tactical::Flag_Cell (YR 0x006DA7D0).
// During a dirty redraw, lists a mapped (or newly revealed) cell not yet
// flagged this frame for redrawing when its ground pixel lies near the
// tactical area, and marks the view to redraw.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/cd_timer.hpp"

void Tactical::Unknown_006AADD0(CellClass *cell)
{
    if (Map.IsToRedraw == 0 && cell->unknown_5c != Frame && ((cell->unknown_12c & 8) || cell->unknown_138)) {
        cell->unknown_5c = Frame;

        CoordStruct coord = cell->unknown_475d60();

        CoordStruct ground = CoordStruct(coord.X, coord.Y, 0);

        Point2D pixel;
        if ((cell->unknown_12c & 8) && (cell->unknown_12c & 0x10)) {
            Coord_To_Pixel(ground, pixel);
        } else {
            Coord_To_Pixel(ground, pixel);
        }

        if (pixel.X >= unknown_rect_839630.X - 30
            && pixel.Y >= -30
            && pixel.X <= unknown_rect_839630.X + unknown_rect_839630.Width + 30
            && pixel.Y <= unknown_rect_839630.Y + unknown_rect_839630.Height + 15) {

            if (unknown_e0 < 799) {
                unknown_e4[unknown_e0] = cell;
                unknown_e0++;
            }
            cell->unknown_138 = false;
            unknown_d7d = true;
        }
    }
}
