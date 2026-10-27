// bool __fastcall From_Buffer(Surface &surface, Rect const &rect, Buffer &buffer) (0x00434A20)
// Copies buffer (packed rows) into rect of surface through a temporary
// BSurface over the buffer memory; false for an empty rect.
#include "shared/blit.hpp"

bool __fastcall From_Buffer(Surface &surface, Rect const &rect, Buffer &buffer)
{
    if (!rect.Is_Valid()) {
        return false;
    }
    BSurface from(rect.Width, rect.Height, surface.Bytes_Per_Pixel(), buffer.Get_Buffer());
    return surface.Copy_From(rect, from, Rect(0, 0, rect.Width, rect.Height), false, true);
}
