// WorldDominationTour::FactionSelectDialogControl::~FactionSelectDialogControl() -- 0x00768800
// Deletes the three faction images; the deleting destructor 0x00769740 inlines it.
#include "shared/wdt_faction_select.hpp"
#include "shared/surface.hpp"
// @ref ??_7FactionSelectDialogControl@WorldDominationTour@@6B@=007af9dc
// @ref ??1DialogControl@OwnerDraw@@UAE@XZ=006010e0

namespace WorldDominationTour {

FactionSelectDialogControl::~FactionSelectDialogControl()
{
    delete Images[0];
    delete Images[1];
    delete Images[2];
}

}
