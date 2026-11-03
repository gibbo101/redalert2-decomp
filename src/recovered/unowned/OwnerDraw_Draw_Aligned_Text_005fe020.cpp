#include "shared/owner_draw_dialog_control.hpp"
#include "shared/text_print.hpp"
#include "shared/hicolor.hpp"
namespace OwnerDraw {
int __fastcall unknown_draw_text_5fe020(Surface *surface, wchar_t const *text, RECT *area, BitFontClass *font,
    unsigned long color, int flags, int unknown7, int unknown8, int arg9, int arg10)
{
    unsigned int pixel = (((unsigned char)color >> (unsigned char)unknown_shift_852fbc) << unknown_shift_852fb8)
        | (((unsigned char)(color >> 16) >> (unsigned char)unknown_shift_852fc4) << unknown_shift_852fc0)
        | (((unsigned char)((unsigned short)color >> 8) >> (unsigned char)unknown_shift_852fcc) << unknown_shift_852fc8);
    int x=area->left;
    int y=area->top;
    int width=area->right-x;
    int height=area->bottom-y;
    if(flags & 4) {
        int text_width,text_height;
        font->Get_Text_Area(text,&text_width,&text_height,width);
        y+=(height-text_height)/2;
    }
    font->Set_Clipping(1);
    font->Set_Clip_Box((tagRECT const *)area);
    font->Set_Color((unsigned short)pixel);
    BitText->Print_Box(font,surface,text,x,y,width,height,flags,arg9,arg10);
    return 0;
}
}
