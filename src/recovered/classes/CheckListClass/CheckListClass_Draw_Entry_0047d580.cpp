// void CheckListClass::Draw_Entry(int index, int x, int y, int width, int selected) (0x0047D580, slot 50)
// Draws an entry as its check mark (character 3, or a blank) and a blank
// before the text, in ListClass::Draw_Entry's style.
#include "shared/check_list.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?Fancy_Clip_Text_Print@@YI?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@PAVColorScheme@@IIIPBH@Z=00497e80
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480
// @ref _swprintf=00783764

extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);

void CheckListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
    if (index < Count()) {
        CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
        if (object != 0) {
            wchar_t buffer[100] = {0};
            buffer[0] = object->IsChecked ? 3 : L' ';
            buffer[1] = L' ';
            swprintf(&buffer[2], object->Text);
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
            Fancy_Clip_Text_Print(buffer, unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &point,
                                  ColorSchemes[scheme], 0, flags, width, Tabs);
        }
    }
}
