// bool Cell::Unknown_00493C80() (0x00493C80)
// Removes the crate overlay (one of Rules' three crate images) from the cell,
// redraws the area it covered and clears the cell's overlay data.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100

bool Cell::Unknown_00493C80()
{
    if (Map.Unknown_0054AAB0(*this)) {
        CellClass &cell = Map[*this];
        if (cell.OverlayIndex != -1) {
            OverlayTypeClass *type = OverlayTypes[cell.OverlayIndex];
            if (type == Rules->unknown_f0 || type == Rules->unknown_f4 || type == Rules->unknown_f8) {
                Rect rect = Union(cell.unknown_474eb0(), cell.unknown_475100());
                rect.Y -= unknown_int_839634;
                unknown_tactical_83996c->Register_Dirty_Area(rect, 0);
                cell.OverlayIndex = -1;
                cell.OverlayData = 0;
                return true;
            }
        }
    }
    return false;
}
