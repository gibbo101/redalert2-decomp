// void WorldDominationTour::FactionSelectDialogControl::Draw_00768940(int unknown) -- 0x00768940
// Clears the current image's area of the background surface and copies the image there.
#include "shared/wdt_faction_select.hpp"
#include "shared/surface.hpp"
#include "shared/rect.hpp"
#include "shared/unknown_globals.hpp"

namespace WorldDominationTour {

void FactionSelectDialogControl::Draw_00768940(int unknown)
{
    if (unknown_surface_839958 != 0 && Current != 0) {
        Rect rect = Current->Get_Rect();
        unknown_surface_839958->Fill_Rect(rect, 0);
        unknown_surface_839958->Copy_From(rect, *Current, rect, false, true);
    }
}

}
