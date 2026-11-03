#include "shared/owner_draw_dialog_control.hpp"
#include "shared/text_print.hpp"
#include "shared/hicolor.hpp"
int __fastcall unknown_text_draw_005fe1b0(unsigned int color, BitFontClass *font, Rect const &area, wchar_t const *text,
    int length, int x_alignment, int y_alignment, Surface *surface, int unknown9)
{
    if (!unknown_flag_a40d28) return 0;
    if (!surface) surface = unknown_surface_839958;
    unsigned int pixel = (((unsigned char)color >> (unsigned char)unknown_shift_852fbc) << unknown_shift_852fb8)
        | (((unsigned char)((unsigned short)color >> 8) >> (unsigned char)unknown_shift_852fcc) << unknown_shift_852fc8)
        | (((unsigned char)(color >> 16) >> (unsigned char)unknown_shift_852fc4) << unknown_shift_852fc0);
    int x = area.X;
    int y = area.Y;
    int width = area.Width;
    int height = area.Height;
    if (!font) font = BitFont;
    int text_width, text_height;
    font->Get_Text_Area(text, &text_width, &text_height, width);
    if (x_alignment == 1) x += (width - text_width + 1) / 2;
    else if (x_alignment == 2) x -= (text_width + 1) / 2;
    else if (x_alignment == 3) x += -1 - text_width;
    else if (x_alignment == 4) x += width - text_width - 1;
    if (y_alignment == 1) y += (height - text_height + 1) / 2;
    else if (y_alignment == 2) y -= (text_height + 1) / 2;
    else if (y_alignment == 3) y += -1 - text_height;
    tagRECT clip;
    clip.left = area.X;
    clip.top = area.Y;
    clip.right = clip.left + width;
    clip.bottom = clip.top + height;
    font->Set_Clipping(1);
    font->Set_Clip_Box(&clip);
    font->Set_Color((unsigned short)pixel);
    int end = BitText->Print(font, surface, text, x, y, length, unknown9);
    return end - x;
}
