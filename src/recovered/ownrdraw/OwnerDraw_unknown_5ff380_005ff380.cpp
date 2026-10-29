// @ref ?unknown_surface_count_a763d8@OwnerDraw@@3HA=00a763d8
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Deletes a registered control's surface (+0x10).
void __fastcall unknown_5ff380(unsigned int key)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    if (record && record->surface_10) {
        delete record->surface_10;
        record->surface_10 = 0;
        --unknown_surface_count_a763d8;
    }
}

}
