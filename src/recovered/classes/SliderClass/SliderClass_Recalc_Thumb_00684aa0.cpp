// void SliderClass::Recalc_Thumb() (0x00684AA0)
// The thumb's pixel size (at least 4) and start for the current value.
#include "shared/gadget.hpp"

void SliderClass::Recalc_Thumb()
{
    int length = IsHorizontal ? Width : Height;
    int size = (int)((double)Thumb / MaxValue * length);
    ThumbSize = (size > 4) ? size : 4;
    int start = (int)((double)CurValue / MaxValue * length);
    ThumbStart = (start < length - ThumbSize) ? start : length - ThumbSize;
}
