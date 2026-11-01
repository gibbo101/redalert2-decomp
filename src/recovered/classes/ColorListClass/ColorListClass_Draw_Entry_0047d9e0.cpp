// void ColorListClass::Draw_Entry(int index, int x, int y, int width, int selected) (0x0047D9E0, slot 50)
// An unselected entry prints in its own colour scheme; a selected one in the selection style:
// 0 its own scheme, 1 the selection scheme (bright for the 6-point fonts), 2 a box in the
// selection colour, 3 a bar under the text, 4 inverted (a bar in the entry's colour).
// The selection scheme is SelectColor, or the entry's index when none is set (Westwood's
// COLRLIST.CPP Draw_Entry).
#include "shared/color_list.hpp"

void ColorListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
    int color;

    if (!selected) {
        Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                              ColorSchemes[Colors[index]], 0, TextFlags, width, Tabs);
        return;
    }

    if (SelectColor == 0) {
        color = index;
    } else {
        color = SelectColor;
    }

    switch (Style) {
        case 0:
            Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                  ColorSchemes[Colors[index]], 0, TextFlags, width, Tabs);
            break;

        case 1:
            if (TextFlags & 6) {
                Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                      ColorSchemes[color], 0, TextFlags | 0x2000, width, Tabs);
            } else {
                Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                      ColorSchemes[color], 0, TextFlags, width, Tabs);
            }
            break;

        case 2:
            unknown_surface_83995c->Draw_Rect(Rect(x, y, x + width - 2, y + LineHeight - 2),
                                              unknown_drawer_8323c4->Convert(ColorSchemes[color]->unknown_0x314));
            Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                  ColorSchemes[Colors[index]], 0, TextFlags, width, Tabs);
            break;

        case 3:
            if (TextFlags & 6) {
                unknown_surface_83995c->Fill_Rect(Rect(x, y, width, LineHeight),
                                                  unknown_drawer_8323c4->Convert(ColorSchemes[color]->unknown_0x314));
                Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                      ColorSchemes[Colors[index]], 0, TextFlags | 0x2000, width, Tabs);
            } else {
                unknown_surface_83995c->Fill_Rect(Rect(x, y, width - 1, LineHeight - 1),
                                                  unknown_drawer_8323c4->Convert(ColorSchemes[color]->unknown_0x314));
                Fancy_Clip_Text_Print(List[index], unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, y),
                                      ColorSchemes[Colors[index]], 0, TextFlags, width, Tabs);
            }
            break;

        case 4:
            unknown_surface_83995c->Fill_Rect(Rect(x, y, width, LineHeight),
                                              unknown_drawer_8323c4->Convert(ColorSchemes[Colors[index]]->unknown_0x314));
            break;
    }
}
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Fancy_Clip_Text_Print@@YI?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@PAVColorScheme@@IIIPBH@Z=00497e80
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
