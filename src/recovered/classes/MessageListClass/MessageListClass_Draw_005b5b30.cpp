// void MessageListClass::Draw() -- 0x005B5B30
// Draws the open edit line, with its cursor character after the text while it has the focus and the
// text is shorter than MaxChars, then the messages.
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPB_WH@Z=00431690
// @ref ?Fancy_Text_Printf@@YA?AVPoint2D@@PB_WPAVSurface@@PBVRect@@PAV1@PAVColorScheme@@IIZZ=00497b40
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/text_print.hpp"
#include "shared/color_scheme.hpp"
#include "shared/mouse.hpp"
#include "shared/unknown_globals.hpp"

void MessageListClass::Draw()
{
    unsigned short cursor[2];
    cursor[0] = 0;
    cursor[1] = 0;
    if (IsEdit) {
        WWMouse->Hide_Mouse();
        EditLabel->Draw_Me(true);
        BitFontClass *font = Font_For_Style(EditLabel->Style);
        int width = font->String_Pixel_Width(EditLabel->Text, 0);
        if (EditCursor != 0 && EditCurPos - EditInitPos < MaxChars - 1 && EditLabel->Has_Focus()) {
            cursor[0] = EditCursor;
            Point2D at(EditLabel->X + width, EditLabel->Y);
            Fancy_Text_Printf((wchar_t const *)cursor, unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &at,
                ColorSchemes[EditLabel->Color], 0, EditLabel->Style);
        }
        WWMouse->Show_Mouse();
    }
    if (First) {
        First->Draw_All(true);
    }
}
