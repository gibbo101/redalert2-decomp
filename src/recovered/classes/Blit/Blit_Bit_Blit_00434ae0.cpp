// bool __fastcall Bit_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect, Blitter const &blitter, int, int, int, int) (0x00434AE0)
// Blits with the surfaces' own rectangles as clipping windows.
#include "shared/blit.hpp"
// @ref ?Bit_Blit@@YI_NAAVSurface@@ABVRect@@1011ABVBlitter@@HHHH@Z=00434b40

bool __fastcall Bit_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect,
                         Blitter const &blitter, int unknown1, int unknown2, int unknown3, int unknown4)
{
    return Bit_Blit(dest, dest.Get_Rect(), destrect, source, source.Get_Rect(), sourcerect, blitter,
                    unknown1, unknown2, unknown3, unknown4);
}
