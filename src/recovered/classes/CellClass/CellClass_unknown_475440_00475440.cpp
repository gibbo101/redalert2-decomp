// Point2D CellClass::unknown_475440() const (0x00475440)
// Westwood's Overlay_Draw_Offset: the pixel offset of the cell's overlay
// image: the overlay's draw offset, raised on a bridge cell (+0x140 bit 7;
// further for the high bridge overlay frames 9-17) or for overlay 0xEF,
// moved by the tactical Y (0x00839634) less the cell level and by the half
// tile (30, 15). Never inlined by its four callers (474830, 4749C0, 474EB0,
// 475100): this declare-then-assign, `offset = offset + ...` form is over
// VC6's auto-inline size cap.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
// @ref ?unknown_int_839634@@3HA=00839634

Point2D CellClass::unknown_475440() const
{
    Point2D offset;
    offset = OverlayClass::Draw_Offset(OverlayIndex);
    if (unknown_140 & 0x80) {
        offset.Y -= 16;
        if (OverlayData >= 9 && OverlayData <= 17) {
            offset.Y -= 15;
        }
    } else if (OverlayIndex == 0xEF) {
        offset.Y -= 15;
    }
    offset.Y += unknown_int_839634 - unknown_11b * 15;
    offset = offset + Point2D(30, 15);
    return offset;
}
