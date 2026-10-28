// Point2D CellClass::unknown_475440() const (0x00475440)
// The pixel offset of the cell's overlay image: the overlay's draw offset,
// raised on a bridge cell (+0x140 bit 7; further for the high bridge
// overlay frames 9-17) or for overlay 0xEF, moved 30 right and down by the
// screen offset at 0x00839634 less the cell level.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
// @ref ?unknown_int_839634@@3HA=00839634

Point2D CellClass::unknown_475440() const
{
    Point2D offset = OverlayClass::Draw_Offset(OverlayIndex);
    if (unknown_140 & 0x80) {
        offset.Y -= 16;
        if (OverlayData >= 9 && OverlayData <= 17) {
            offset.Y -= 15;
        }
    } else if (OverlayIndex == 0xEF) {
        offset.Y -= 15;
    }
    offset.Y += unknown_int_839634 - unknown_11b * 15;
    return Point2D(offset.X + 30, offset.Y + 15);
}
