// bool __fastcall To_Buffer(Surface &surface, Rect const &rect, Buffer &buffer) (0x00434960)
// Copies rect of surface into buffer (packed rows) through a temporary
// BSurface over the buffer memory; false for an empty rect.
// Unresolved: the meaning of the last Copy_From flag (passed true).
#include "shared/blit.hpp"
// @ref ?Copy_From@XSurface@@UAE_NABVRect@@AAVSurface@@0_N2@Z=00774f00

bool __fastcall To_Buffer(Surface &surface, Rect const &rect, Buffer &buffer)
{
    if (!rect.Is_Valid()) {
        return false;
    }
    BSurface to(rect.Width, rect.Height, surface.Bytes_Per_Pixel(), buffer.Get_Buffer());
    return to.Copy_From(Rect(0, 0, rect.Width, rect.Height), surface, rect, false, true);
}
