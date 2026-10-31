// Complete cached-voxel blit: 710 body bytes and 10 frozen NOPs.
#include "shared/voxel_cache.hpp"
#include "shared/convert.hpp"
#include "shared/blit.hpp"
extern ConvertClass *unknown_drawer_ad0608;
extern Rect unknown_unit_rect_ad0490;
// @ref ?unknown_drawer_ad0608@@3PAVConvertClass@@A=00ad0608
// @ref ?unknown_unit_rect_ad0490@@3VRect@@A=00ad0490
// @ref ?RLEBlitter_From_Flags_00485d60@ConvertClass@@QBEPBVRLEBlitter@@I@Z=00485d60
void TechnoClass::Blit_Voxel_006d29d0(void const *image,Point2D const &point,Rect const &cliprect,unsigned flags,int brightness)
{
    StaticBufferClass::Entry const &entry=*static_cast<StaticBufferClass::Entry const *>(image);
    BSurface surface(entry.Width,entry.Height,1,entry.Data);
    flags&=~0x10U;
    ConvertClass *converter;
    if (Kind_Of()==1 && static_cast<UnitClass *>(this)->unknown_5bb) converter=unknown_drawer_ad0608;
    else converter=(ConvertClass *)unknown_slot115();
    RLEBlitter const *blitter=converter->RLEBlitter_From_Flags_00485d60(flags);
    int phase=0;
    if (flags&8) phase=(Fetch_ID()+(int)unknown_1e0)%400;
    if (Kind_Of()==1) {
        unknown_unit_rect_ad0490=Union(unknown_unit_rect_ad0490,Rect(entry.X+point.X,entry.Y+point.Y,entry.Width,entry.Height));
    }
    if (blitter) {
        RLE_Blit(*unknown_surface_83995c,cliprect,Rect(entry.X+point.X,entry.Y+point.Y,entry.Width,entry.Height),surface,surface.Get_Rect(),surface.Get_Rect(),*blitter,unknown_slot176(),unknown_slot177(),brightness,phase,0,BlitPair(0,0));
    }
}
// @ref ??0Surface@@QAE@HH@Z=0049ed90
