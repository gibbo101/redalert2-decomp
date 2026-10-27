// bool __fastcall RLE_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect, RLEBlitter const &blitter, int, int, int, int) (0x00435060)
// RLE blit with the surfaces' own rectangles as clipping windows.
#include "shared/blit.hpp"
// @ref ?RLE_Blit@@YI_NAAVSurface@@ABVRect@@1011ABVRLEBlitter@@HHHHHUBlitPair@@@Z=004350c0

bool __fastcall RLE_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect,
                         RLEBlitter const &blitter, int unknown1, int unknown2, int unknown3, int unknown4)
{
    return RLE_Blit(dest, dest.Get_Rect(), destrect, source, source.Get_Rect(), sourcerect, blitter,
                    unknown1, unknown2, unknown3, unknown4, 0, BlitPair(0, 0));
}
