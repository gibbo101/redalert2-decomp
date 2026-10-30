// 0043EBA0: replace the footprint with rubble and optionally leave a crate.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/tactical.hpp"
extern Rect unknown_rect_839630; // existing declaration in shared/display.hpp
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??0Rect@@QAE@ABUTPoint2D@@HH@Z=00453e40
static inline bool Is_List_End(Cell const *offset);
void BuildingClass::Leave_Rubble_0043eba0()
{
    void *image;
    int frame;
    if (Type->unknown_func_458e00(&image, &frame)) {
        Cell const *offset = unknown_slot64(0);
        Cell origin = Coord_Cell(unknown_slot42());
        while (!Is_List_End(offset)) {
            Cell position = *offset++ + origin;
            CellClass &cell = Map[position];
            cell.unknown_47c080();
            cell.OverlayIndex = 0xef;
            cell.unknown_40 = 0;
            cell.Unknown_00472540(-1);
            Map.Unknown_0054FB20(cell.MapCoords);
            Map.Unknown_00566340(cell.MapCoords);
            Unknown_006D7C80(&cell);
        }
        CellClass &base = Map[origin];
        base.unknown_40 = Type;
        Rect area = Union(base.unknown_474eb0(), base.unknown_475100());
        Point2D view_origin(unknown_rect_839630.X, unknown_rect_839630.Y);
        Point2D translated(area.X - view_origin.X, area.Y - view_origin.Y);
        unknown_tactical_83996c->Unknown_006A3020(Rect(TPoint2D(translated.X, translated.Y), area.Width, area.Height), 0);
        unknown_tactical_83996c->Unknown_006AADD0(&Map[origin]);
    }
    if (Type->CrateBeneath) {
        Cell position = Coord_Cell(unknown_slot42());
        if (Type->CrateBeneathIsMoney) {
            Map.Unknown_0054E580(position, 0);
            return;
        }
        Map.Unknown_0054E580(position, 0x14);
    }
}
