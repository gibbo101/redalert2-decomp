// bool Bit_Blit_Plain(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect) (0x00775560)
// Copies sourcerect of source to destrect of dest with the plain blitter for
// dest's pixel size. The name is a hypothesis (Westwood's Bit_Blit overload
// without the transparency flag); the calling convention is __fastcall like
// Bit_Blit itself.
#include "shared/blitter.hpp"
#include "shared/surface.hpp"
// @ref ?Bit_Blit@@YI_NAAVSurface@@ABVRect@@01ABVBlitter@@HHHH@Z=00434ae0
// @ref ??_7?$BlitPlain@G@@6B@=007afc84
// @ref ??_7?$BlitPlain@E@@6B@=007afc94

bool __fastcall Bit_Blit_Plain(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect)
{
    if (dest.Bytes_Per_Pixel() == 1) {
        return Bit_Blit(dest, destrect, source, sourcerect, BlitPlain<unsigned char>(), 0, 3, 1000, 0);
    }
    return Bit_Blit(dest, destrect, source, sourcerect, BlitPlain<unsigned short>(), 0, 3, 1000, 0);
}
