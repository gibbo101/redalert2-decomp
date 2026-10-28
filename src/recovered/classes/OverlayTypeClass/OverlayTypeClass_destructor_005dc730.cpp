// OverlayTypeClass::~OverlayTypeClass() (0x005DC730)
// Leaves the notice lists and OverlayTypes.
#include "shared/overlay_type.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60

OverlayTypeClass::~OverlayTypeClass()
{
    Unknown_006ECB90((ObjectClass *)(AbstractClass *)this, true);
    OverlayTypes.Delete(this);
}
