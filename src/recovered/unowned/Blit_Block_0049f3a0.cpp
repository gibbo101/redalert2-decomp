#include "shared/surface_blit.hpp"
#include "shared/convert.hpp"
#include "shared/blit.hpp"
// Existing callers use integer pointer bits for remap/blitter; preserve that public ABI.
void __fastcall unknown_blit_49f3a0(Surface &dest,void *converter,Surface &source,Rect const &source_rect,
                                  RectPoint2D const &point,Rect const &window,int remap_bits,int blitter_bits,
                                  int height_offset,int gradient,int intensity,int unknown)
{
    ConvertClass *convert=static_cast<ConvertClass *>(converter);
    convert->ActiveRemap=reinterpret_cast<unsigned char const *>(remap_bits);
    Blitter const *blitter=reinterpret_cast<Blitter const *>(blitter_bits);
    if(!blitter) blitter=convert->Select_Blitter_00485AA0(remap_bits ? 16 : 0);
    Bit_Blit(dest,window,Rect(point.X,point.Y,source_rect.Width,source_rect.Height),source,source.Get_Rect(),source_rect,*blitter,height_offset,gradient,intensity,unknown);
}
