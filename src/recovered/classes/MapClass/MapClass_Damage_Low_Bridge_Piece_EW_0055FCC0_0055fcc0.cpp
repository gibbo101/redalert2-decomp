#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ?Spring_Low_Bridge_Destroyed_NS@MapClass@@QAEXVCell@@@Z=0055e930
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540
// @ref ?Unknown_0047CC10@CellClass@@QAEXXZ=0047cc10
// @ref ??$Union@VRect@@@@YI?BVRect@@ABV0@0@Z=0045efe0
// @ref ??GRectPoint2D@@QBE?AU0@ABU0@@Z=0047d040
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Unknown_00631570@RadarClass@@QAEXABVCell@@@Z=00631570
// @ref ?Unknown_0054EBD0@MapClass@@QAEHXZ=0054ebd0
// @ref ?Unknown_005687B0@MapClass@@QAEXABVRect@@@Z=005687b0

extern Rect unknown_rect_839630;
inline RectPoint2D Rect::Top_Left() const { return RectPoint2D(X, Y); }
inline Rect Rect::operator-(RectPoint2D const &point) const { return Rect(Top_Left() - point, Width, Height); }
// Damage one low-bridge piece using its neighboring span mask, original0055FCC0.
void MapClass::Damage_Low_Bridge_Piece_EW_0055FCC0(Cell const &cell)
{
    if (!Unknown_00562930(cell)) return;
    CellClass *center = &Map[cell];
    CellClass *side1 = &Map[cell - Cell(0, 1)];
    CellClass *side2 = &Map[cell + Cell(0, 1)];
    Rect draw_rect = Union(center->unknown_474eb0(), center->unknown_475100());
    int lookup[16] = { -1, 0x4f, 0x52, -1, 0x4e, 0x50, 0x52, -1, 0x51, 0x51, 0x64, -1, -1, -1, -1, -1 };
    int mask = Unknown_0055DA70(cell);
    int current = Map[cell].OverlayIndex;
    if (mask > 0) {
        int next;
        if (current >= 0x5c) {
            if (current == 0x5c) next = 0x5d;
            else if (current == 0x5e) next = 0x5f;
            else return;
        } else {
            next = lookup[mask];
            if (current == next) return;
        }
        side2->OverlayIndex = side1->OverlayIndex = center->OverlayIndex = next;
        draw_rect = Union(draw_rect, Union(center->unknown_474eb0(), center->unknown_475100())) - unknown_rect_839630.Top_Left();
        unknown_tactical_83996c->Register_Dirty_Area(draw_rect, false);
        if (next == 0x64) {
            Map.Unknown_00631570(cell);
            Map.Unknown_00631570(cell + Cell(0, 1));
            Map.Unknown_00631570(cell - Cell(0, 1));
        }
        center->Unknown_00472540(-1);
        side1->Unknown_00472540(-1);
        side2->Unknown_00472540(-1);
        center->Unknown_0047CC10();
        side1->Unknown_0047CC10();
        side2->Unknown_0047CC10();
    }
}
