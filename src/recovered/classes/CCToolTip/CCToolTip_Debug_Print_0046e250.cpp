// CCToolTip text-box drawing, original0046E250; existing slot4 contract retained.
#include "shared/tool_tip.hpp"
#include "shared/text_print.hpp"
extern RGBClass unknown_color_ac1028;
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?BitText@@3PAVBitTextClass@@A=0084e9d0
// @ref ?Get_Text_Area@BitFontClass@@QAE_NPBGPAH1H@Z=004314b0
// @ref ?Print_Box@BitTextClass@@QAE_NPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?Set_Clip_Box@BitFontClass@@QAEXPBUtagRECT@@@Z=00431460
// @ref ?Set_Clipping@BitFontClass@@QAEEE@Z=00431450
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ?unknown_color_ac1028@@3VRGBClass@@A=00ac1028
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_flag_abcd84@@3_NA=00abcd84
// @ref ?unknown_rect_839620@@3VRect@@A=00839620
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
void CCToolTip::Debug_Print(ToolTipRecord *record)
{
    Rect box;
    int x = record->unknown_00;
    int y = record->unknown_04;
    Surface *surface = 0;
    if (unknown_flag_a40b30 == true) {
        int boundary = unknown_rect_839630.X + unknown_rect_839630.Width;
        if (x + record->unknown_08 <= boundary) surface = unknown_surface_839964;
        else if (unknown_260 == true && x >= boundary) {
            surface = unknown_surface_839948;
            x -= boundary;
            unknown_flag_abcd84 = true;
        }
    } else {
        int boundary = unknown_rect_839620.X + unknown_rect_839620.Width;
        if (x >= boundary) {
            surface = unknown_surface_839964;
            x -= boundary;
        } else if (unknown_260 == true && x + record->unknown_08 < boundary) {
            surface = unknown_surface_839948;
            unknown_flag_abcd84 = true;
        }
    }
    if (surface) {
        BitFontClass *font = BitFont;
        tagRECT area;
        area.left = x;
        area.top = y;
        area.right = x;
        area.bottom = y;
        wchar_t const *text = record->Text;
        int width, height;
        font->Get_Text_Area(text, &width, &height, surface->Get_Width());
        area.right = width + area.left;
        area.bottom = height + area.top;
        int box_width = area.right - area.left + 8;
        int box_height = area.bottom - area.top + 4;
        if (area.left + box_width > surface->Get_Width()) {
            area.left = surface->Get_Width() - box_width;
        }
        area.right = box_width + area.left;
        area.bottom = box_height + area.top;
        int color = Build_Hicolor_Pixel(unknown_color_ac1028.Red, unknown_color_ac1028.Green, unknown_color_ac1028.Blue);
        box.Set(area.left, area.top, box_width, box_height);
        surface->Fill_Rect(box, 0);
        surface->Draw_Rect(box, color);
        font->Set_Clipping(1);
        font->Set_Clip_Box(&area);
        font->Set_Color((unsigned short)color);
        BitText->Print_Box(font, surface, text, area.left + 4, area.top + 2,
            area.right - area.left, area.bottom - area.top, 0, 0, 0);
    }
}
