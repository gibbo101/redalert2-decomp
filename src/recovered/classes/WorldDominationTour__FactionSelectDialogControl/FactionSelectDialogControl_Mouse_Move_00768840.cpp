// void WorldDominationTour::FactionSelectDialogControl::Mouse_Move_00768840(HWND window, Point2D const &point)
// (0x00768840): picks the image and selection under the point (the allied and soviet map areas) and
// repaints the window when the selection changes.
#include "shared/wdt_faction_select.hpp"
#include "shared/rect.hpp"
#include "shared/win32_api.hpp"

namespace WorldDominationTour {

void FactionSelectDialogControl::Mouse_Move_00768840(HWND window, Point2D const &point)
{
    if (unknown_slot2()) {
        return;
    }
    Current = NoneImage;
    int selection = 0;
    if (Rect(16, 20, 348, 116).Is_Point_Within(point) || Rect(130, 100, 170, 116).Is_Point_Within(point) || Rect(175, 216, 70, 46).Is_Point_Within(point)) {
        Current = AlliedImage;
        selection = 2;
    } else if (Rect(252, 180, 214, 202).Is_Point_Within(point) || Rect(212, 262, 284, 160).Is_Point_Within(point)) {
        Current = SovietImage;
        selection = 3;
    }
    if (Selection != selection) {
        Selection = selection;
        InvalidateRect(window, 0, FALSE);
    }
}

}
