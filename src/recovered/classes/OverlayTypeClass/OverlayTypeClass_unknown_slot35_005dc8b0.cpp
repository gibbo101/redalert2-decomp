// ObjectClass *OverlayTypeClass::unknown_slot35(HouseClass *house) const (0x005DC8B0)
// Creates an unplaced overlay of this type (at the zero cell).
#include "shared/overlay_type.hpp"
#include "shared/overlay.hpp"
// @ref ??0OverlayClass@@QAE@PAVOverlayTypeClass@@ABVCell@@H@Z=005da7d0

ObjectClass *OverlayTypeClass::unknown_slot35(HouseClass *house) const
{
    return new OverlayClass((OverlayTypeClass *)this, unknown_geometry_k, -1);
}
