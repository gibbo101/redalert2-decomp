// void ListClass::Draw_Entry(int index, int x, int y, int width, int selected) (0x0053A6E0, slot 50)
// Prints one entry clipped to `width` with the list's tab stops in the box
// colour scheme: a selected entry is bright (0x2000) on a bar of the
// scheme's palette index +0x31C; others get 0x1000 unless their flags have
// 0x4000 (Westwood's ListClass::Draw_Entry shape).
#include "shared/gadget.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?Fancy_Clip_Text_Print@@YI?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@PAVColorScheme@@IIIPBH@Z=00497e80

void ListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
    unsigned flags = TextFlags;
    int scheme = unknown_scheme_index_4cefc0();

    if (selected) {
        flags |= 0x2000;
        unknown_surface_83995c->Fill_Rect(Rect(x, y, width, LineHeight),
                                          unknown_drawer_8323c4->Convert(ColorSchemes[scheme]->unknown_color_0x31c));
    } else if (!(flags & 0x4000)) {
        flags |= 0x1000;
    }
    Point2D point(x, y);
    Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &point,
                          ColorSchemes[scheme], 0, flags, width, Tabs);
}
