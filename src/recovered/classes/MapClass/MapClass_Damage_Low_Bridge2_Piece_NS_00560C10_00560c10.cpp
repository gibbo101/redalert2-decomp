#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ?Spring_Low_Bridge_Destroyed_NS@MapClass@@QAEXVCell@@@Z=0055e930
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540
// @ref ?Unknown_0047CC10@CellClass@@QAEXXZ=0047cc10
// @ref ??$Union@VRect@@@@YI?AVRect@@ABV0@0@Z=0045efe0
// @ref ??GRectPoint2D@@QBE?AU0@ABU0@@Z=0047d040
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Unknown_00631570@RadarClass@@QAEXABVCell@@@Z=00631570
// @ref ?Unknown_0054EBD0@MapClass@@QAEXXZ=0054ebd0
// @ref ?Unknown_005687B0@MapClass@@QAEXABVRect@@@Z=005687b0

extern Rect unknown_rect_839630;
// Damage one low-bridge piece using its neighboring span mask, original00560C10.
void MapClass::Damage_Low_Bridge2_Piece_NS_00560C10(Cell const &cell)
{
    if (!Unknown_00562980(cell)) return;
    CellClass *center = &Map[cell];
    CellClass *side1 = &Map[cell - Cell(1, 0)];
    CellClass *side2 = &Map[cell + Cell(1, 0)];
    Rect draw_rect = Union(center->unknown_474eb0(), center->unknown_475100());
    int lookup[16] = { -1, 0xdb, 0xde, -1, 0xda, 0xdc, 0xde, -1, 0xdd, 0xdd, 0xe8, -1, -1, -1, -1, -1 };
    int mask = Unknown_0055ECA0(cell);
    int current = center->OverlayIndex;
    if (mask > 0) {
        int next;
        if (current >= 0xe3) {
            if (current == 0xe3) next = 0xe4;
            else if (current == 0xe5) next = 0xe6;
            else return;
        } else {
            next = lookup[mask];
            if (next == current) return;
        }
        side2->OverlayIndex = side1->OverlayIndex = center->OverlayIndex = next;
        draw_rect = Union(draw_rect, Union(center->unknown_474eb0(), center->unknown_475100())) - unknown_rect_839630.Top_Left();
        unknown_tactical_83996c->Register_Dirty_Area(draw_rect, false);
        if (next == 0xe8) {
            Map.Unknown_00631570(cell);
            Map.Unknown_00631570(cell + TPoint2D<short>(1, 0));
            Map.Unknown_00631570(cell - Cell(1, 0));
        }
        center->Unknown_00472540(-1);
        side1->Unknown_00472540(-1);
        side2->Unknown_00472540(-1);
        center->Unknown_0047CC10();
        side1->Unknown_0047CC10();
        side2->Unknown_0047CC10();
    }
}
