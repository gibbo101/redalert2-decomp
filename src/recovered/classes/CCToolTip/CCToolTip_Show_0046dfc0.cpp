// bool CCToolTip::Show(ToolTipRecord *record) (0x0046DFC0, slot 1)
#include "shared/tool_tip.hpp"
#include "shared/mouse.hpp"
#include "shared/text_print.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?Get_Text_Area@BitFontClass@@QAE_NPBGPAH1H@Z=004314b0
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_rect_839620@@3VRect@@A=00839620
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_flag_8373c2@@3_NA=008373c2

bool CCToolTip::Show(ToolTipRecord *record)
{
    bool mouse_visible = WWMouse->Get_Mouse_State() >= 0;
    if (mouse_visible) {
    BitFontClass *font = BitFont;
    Rect *area = 0;
    if (unknown_flag_a40b30 == true) {
        if (record->unknown_00 > unknown_rect_839630.X + unknown_rect_839630.Width) {
            area = &unknown_rect_839620;
            unknown_flag_8373c2 = true;
        } else {
            area = &unknown_rect_839630;
        }
    } else if (record->unknown_00 <= unknown_rect_839620.X + unknown_rect_839620.Width) {
        area = &unknown_rect_839620;
        unknown_flag_8373c2 = true;
    } else {
        area = &unknown_rect_839630;
    }
    if (area != 0) {
        int width;
        int height;
        font->Get_Text_Area(record->Text, &width, &height, area->Width);
        width += 4;
        height += 3;
        record->unknown_08 = width > record->unknown_08 ? width : record->unknown_08;
        record->unknown_0c = height > record->unknown_0c ? height : record->unknown_0c;
        if (record->unknown_08 >= area->Width) {
            font->Get_Text_Area(record->Text, &width, &height, area->Width - 4);
            width += 4;
            height += 3;
        record->unknown_08 = width > record->unknown_08 ? width : record->unknown_08;
        record->unknown_0c = height > record->unknown_0c ? height : record->unknown_0c;
        }
        ToolTip *tip = Current;
        if (tip == 0 || tip->unknown_18 == false) {
            int over = record->unknown_00 - area->X - area->Width + record->unknown_08;
            if (over > 0) {
                record->unknown_00 -= over;
            }
            record->unknown_04 += 16;
            if (record->unknown_04 - area->Height - area->Y + record->unknown_0c > 0) {
                record->unknown_04 = record->unknown_04 - record->unknown_0c - 16;
            }
        } else {
            Rect region = tip->Region;
            if (region.X < area->Width / 2 + area->X) {
                record->unknown_00 = region.Width - 5 + region.X;
            } else {
                record->unknown_00 = region.X - width + 5;
            }
            record->unknown_00 = area->X > record->unknown_00 ? area->X : record->unknown_00;
            if (region.Y < area->Height / 2 + area->Y) {
                record->unknown_04 = region.Height - 5 + region.Y;
            } else {
                record->unknown_04 = region.Y - height + 5;
            }
            record->unknown_04 = area->Y > record->unknown_04 ? area->Y : record->unknown_04;
        }
    }
    return true;
    }
    return false;
}
