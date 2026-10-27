// static Point2D __fastcall OverlayClass::Draw_Offset(int overlay) (0x005DC050)
// Raises ore, walls, crates and overlay 0x7E by 12 pixels, land type 9
// overlays and overlay 0x7E by one more.
// Assumptions: the purpose (image draw offset) is a hypothesis.
#include "shared/overlay.hpp"

Point2D __fastcall OverlayClass::Draw_Offset(int overlay)
{
    OverlayTypeClass *type = OverlayTypes[overlay];
    Point2D offset(0, 0);
    if (type->Tiberium || type->Wall || type->ArrayIndex == 0x7E || type->Crate) {
        offset.Y = -12;
    }
    if (type->Land == 9) {
        offset.Y--;
    }
    if (overlay == 0x7E) {
        offset.Y--;
    }
    return offset;
}
