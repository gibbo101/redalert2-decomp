// bool Bit_Blit_Trans(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect) (0x007755C0)
// Copies sourcerect of source to destrect of dest with the transparent blitter (colour 0 is skipped) for
// dest's pixel size. The name is a hypothesis (Westwood's Bit_Blit overload
// with the transparency flag set); the calling convention is __fastcall like
// Bit_Blit itself.
#include "shared/blitter.hpp"
#include "shared/surface.hpp"
// @ref ?Bit_Blit@@YI_NAAVSurface@@ABVRect@@01ABVBlitter@@HHHH@Z=00434ae0
// @ref ??_7?$BlitTrans@G@@6B@=007afca4
// @ref ??_7?$BlitTrans@E@@6B@=007afcb4

bool __fastcall Bit_Blit_Trans(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect)
{
    if (dest.Bytes_Per_Pixel() == 1) {
        return Bit_Blit(dest, destrect, source, sourcerect, BlitTrans<unsigned char>(), 0, 3, 1000, 0);
    }
    return Bit_Blit(dest, destrect, source, sourcerect, BlitTrans<unsigned short>(), 0, 3, 1000, 0);
}
