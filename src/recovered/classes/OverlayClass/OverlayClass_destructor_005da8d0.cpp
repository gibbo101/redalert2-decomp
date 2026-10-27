// OverlayClass::~OverlayClass() (0x005DA8D0)
// Leaves the notice lists and the overlay list; leaves the map (ObjectClass
// slot 52) only when the 0x00A40958 flag is set.
#include "shared/overlay.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVObjectClass@@_N@Z=006ecb90
// @ref ?unknown_slot52@ObjectClass@@UAEHXZ=005d3700
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ??1ObjectClass@@UAE@XZ=005d2530

OverlayClass::~OverlayClass()
{
    Unknown_006ECB90(this, true);
    unknown_OverlayClass_list_00a40c00.Delete(this);
    if (unknown_flag_a40958) {
        ObjectClass::unknown_slot52();
    }
    Class = 0;
}
