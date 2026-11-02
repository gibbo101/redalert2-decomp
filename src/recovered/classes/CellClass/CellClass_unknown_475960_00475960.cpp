// void CellClass::unknown_475960(bool flag) (0x00475960): TibSun Wall_Update. For each of the four
// neighbours and the cell itself (0x007D2B58 offsets, -1 last), computes the overlay redraw area
// (Union of 0x00474EB0 and 0x00475100 moved by the tactical origin; the result is unused; skipped for
// the cell itself when flag is set), redraws the cell (0x0047C080) and, for a wall overlay, rebuilds its
// connection bits from the four neighbours and removes incomplete damaged wall stages, updating the
// zones when the passability changes.
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tactical.hpp"
#include "shared/abstract.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_wall_offsets_7d2b58@@3PAHA=007d2b58

extern int unknown_wall_offsets_7d2b58[5];

// An inline operand is evaluated before a plain call: passing the first rectangle through this identity
// helper gives the original's call order (0x00474EB0 before 0x00475100) at the dead redraw-area site.
inline Rect const &Wall_Rect(Rect const &rect) { return rect; }

void CellClass::unknown_475960(bool flag)
{
    for (int *offset = unknown_wall_offsets_7d2b58; offset < &unknown_wall_offsets_7d2b58[5]; offset++) {
        CellClass &newcell = (CellClass &)((CellClass const *)this)->Adjacent_Cell(*offset);
        if (!flag || *offset != -1) {
            Union(Wall_Rect(newcell.unknown_474eb0()), newcell.unknown_475100()) - unknown_rect_839630.Top_Left();
        }
        newcell.unknown_47c080();

        if (newcell.OverlayIndex != -1 && OverlayTypes[newcell.OverlayIndex]->Wall) {
            int icon = 0;
            unsigned i = 0;
            for (int *dir = unknown_wall_offsets_7d2b58; dir < &unknown_wall_offsets_7d2b58[4]; dir++) {
                if (newcell.Adjacent_Cell(*dir).unknown_475840(newcell.OverlayIndex, *dir)) {
                    icon |= 1 << i;
                }
                i++;
            }
            newcell.OverlayData = (newcell.OverlayData & 0xF0) | icon;

            bool recalc_around = false;
            int old_passability = newcell.unknown_4c;
            if ((newcell.OverlayIndex == 2 || newcell.OverlayIndex == 0x1A) && (newcell.OverlayData == 0x30 || newcell.OverlayData == 0x20)) {
                newcell.OverlayIndex = -1;
                newcell.OverlayData = 0;
                Unknown_006ECB90(&newcell, true);
                recalc_around = true;
            }
            if (newcell.OverlayIndex == 0 && (newcell.OverlayData == 0x10 || newcell.OverlayData == 0x20)) {
                newcell.OverlayIndex = -1;
                newcell.OverlayData = 0;
                newcell.unknown_50 = -1;
                Unknown_006ECB90(&newcell, true);
                recalc_around = true;
            }
            if (newcell.OverlayIndex == 1 && newcell.OverlayData == 0x20) {
                newcell.OverlayIndex = -1;
                newcell.OverlayData = 0;
                newcell.unknown_50 = -1;
                Unknown_006ECB90(&newcell, true);
                recalc_around = true;
            }
            if (newcell.OverlayIndex == 0x16 && (newcell.OverlayData == 0x10 || newcell.OverlayData == 0x20)) {
                newcell.OverlayIndex = -1;
                newcell.OverlayData = 0;
                newcell.unknown_50 = -1;
                Unknown_006ECB90(&newcell, true);
                recalc_around = true;
            }
            if (newcell.OverlayIndex == 3 && newcell.OverlayData == 0x10) {
                newcell.OverlayIndex = -1;
                newcell.OverlayData = 0;
                newcell.unknown_50 = -1;
                Unknown_006ECB90(&newcell, true);
                recalc_around = true;
            }

            newcell.Unknown_00472540(-1);

            if (newcell.unknown_4c != old_passability) {
                if (recalc_around) {
                    Map.Unknown_0054FB20(newcell.MapCoords);
                    Map.Unknown_00566340(newcell.MapCoords);
                    for (unsigned dir = 0; dir < 8; dir++) {
                        CellClass &adjacent = Map[Adjacent_Cell(newcell.MapCoords, dir)];
                        adjacent.unknown_122--;
                    }
                } else {
                    Map.Unknown_0054FC60(newcell.MapCoords);
                    Map.Unknown_00566340(newcell.MapCoords);
                }
            }
        }
    }
}
