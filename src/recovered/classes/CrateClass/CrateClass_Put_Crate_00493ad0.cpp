// bool __fastcall CrateClass::Put_Crate(Cell &cell) -- 0x00493AD0
// Places a wood crate (a water crate on water) at cell when the cell is on the map and has no overlay,
// and redraws the area it covers.
#include "shared/crate.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100

bool __fastcall CrateClass::Put_Crate(Cell &cell)
{
    int old = unknown_a40774;
    unknown_a40774 = 0;
    if (!Map.Unknown_0055A660(cell, true)) {
        unknown_a40774 = old;
        return false;
    }
    CellClass *cellptr = &Map[cell];
    if (cellptr->OverlayIndex == -1) {
        if (Map[cell].unknown_ec == 2) {
            new OverlayClass(Rules->unknown_f8, cell);
        } else {
            new OverlayClass(Rules->unknown_f0, cell);
        }
        Rect rect = Union(cellptr->unknown_474eb0(), cellptr->unknown_475100());
        Point2D pt(unknown_int_839630, unknown_int_839634);
        unknown_tactical_83996c->Register_Dirty_Area(Rect(rect.X - pt.X, rect.Y - pt.Y, rect.Width, rect.Height), false);
        unknown_a40774 = old;
        return true;
    }
    unknown_a40774 = old;
    return false;
}
