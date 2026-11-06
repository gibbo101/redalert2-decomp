// Rebuild the east/west low bridge run, original005615A0.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ?Map_Random_Range_005797a0@@YIII@Z=005797a0
// @ref ??$Union@VRect@@@@YI?BVRect@@ABV0@0@Z=0045efe0
// @ref ??GRectPoint2D@@QBE?AU0@ABU0@@Z=0047d040
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Unknown_00631570@RadarClass@@QAEXABVCell@@@Z=00631570
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum, unsigned int maximum);
extern Rect unknown_rect_839630;

void MapClass::Repair_Low_Bridge_EW(Cell const &cell)
{
    // These known 0/1 predicates are consumed through AL in the original.
    unsigned char low_bridge;
    Cell cursor = cell;
    bool changed = false;
    do {
        --cursor.X;
        low_bridge = (unsigned char)Unknown_00562930(cursor);
    } while (low_bridge);
    ++cursor.X;
    Rect recalc_rect(0, 0, 0, 0);
    do {
        CellClass *center = &Map[cursor];
        CellClass *side1 = &Map[cursor - Cell(0, 1)];
        CellClass *side2 = &Map[cursor + Cell(0, 1)];
        Rect draw_rect = Union(center->unknown_474eb0(), center->unknown_475100());
        int old_overlay = center->OverlayIndex;
        int new_overlay = old_overlay;
        switch (old_overlay) {
        case 0x5c: case 0x5d:
            new_overlay = 0x5c;
            break;
        case 0x5e: case 0x5f:
            new_overlay = 0x5e;
            break;
        case 0x4e:
        case 0x4f:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x64:
            new_overlay = Map_Random_Range_005797a0(0, 3) + 0x4a;
            recalc_rect = Union(recalc_rect, Rect(cursor.X, cursor.Y - 1, 1, 3));
            changed = true;
            break;
        default:
            break;
        }
        if (new_overlay != old_overlay) {
            center->OverlayIndex = new_overlay;
            side1->OverlayIndex = new_overlay;
            side2->OverlayIndex = new_overlay;
            draw_rect = Union(draw_rect, Union(center->unknown_474eb0(), center->unknown_475100())) - unknown_rect_839630.Top_Left();
            unknown_tactical_83996c->Register_Dirty_Area(draw_rect, false);
            if (old_overlay == 0x64) {
                Map.Unknown_00631570(cursor);
                Map.Unknown_00631570(cursor + Cell(0, 1));
                Map.Unknown_00631570(cursor - Cell(0, 1));
            }
            center->Unknown_00472540(-1);
            side1->Unknown_00472540(-1);
            side2->Unknown_00472540(-1);
        }
        ++cursor.X;
        low_bridge = (unsigned char)Unknown_00562930(cursor);
    } while (low_bridge);
    if (changed) Unknown_0054EBD0();
    if (recalc_rect.Is_Valid()) Unknown_005687B0(recalc_rect);
}
