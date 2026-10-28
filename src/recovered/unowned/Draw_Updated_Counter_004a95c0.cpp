#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/dsurface.hpp"
extern wchar_t counter_current_text_00852a68[];
extern wchar_t counter_previous_text_00852ab8[];
extern wchar_t const counter_text_format_007d61ec[];
extern char const counter_scheme_007d61e4[];
ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name,int kind);
void __fastcall unknown_blit_49f3a0(Surface &dest,void *convert,Surface &source,Rect const &sourcerect,
    Point2D const &destpoint,Rect const &destclip,int unknown1,int unknown2,int unknown3,int unknown4,int unknown5,int unknown6);
// @ref ?counter_current_text_00852a68@@3PAGA=00852a68
// @ref ?counter_previous_text_00852ab8@@3PAGA=00852ab8
// @ref ?counter_text_format_007d61ec@@3QBGB=007d61ec
// @ref ?counter_scheme_007d61e4@@3QBDB=007d61e4
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref _swprintf=00783764
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
// The original merge retains the inclusive right/bottom adjustment.
inline Rect Merge_Counter_Areas(Rect const &first,Rect const &second)
{
    Rect area=first;
    if(area.X>second.X) {
        area.Width+=area.X-second.X;
        area.X=second.X;
    }
    if(area.Y>second.Y) {
        area.Height+=area.Y-second.Y;
        area.Y=second.Y;
    }
    if(area.X+area.Width<second.X+second.Width)
        area.Width=second.X+second.Width-area.X+1;
    if(area.Y+area.Height<second.Y+second.Height)
        area.Height=second.Y+second.Height-area.Y+1;
    return area;
}
// Restore the union of old/new text bounds, then print the updated value.
void __fastcall Draw_Updated_Counter_004a95c0(int current,int previous,Surface *background,
    Point2D &position,wchar_t const *prefix,bool centered,void *convert,int unknown_blit_flags)
{
    unsigned style=0x46;
    if(centered) style=0x146;
    BitFontClass *font=Font_For_Style(style);
    swprintf(counter_current_text_00852a68,counter_text_format_007d61ec,prefix,current);
    swprintf(counter_previous_text_00852ab8,counter_text_format_007d61ec,prefix,previous);
    int current_x;
    int previous_x;
    if(centered) {
        current_x=position.X-font->String_Pixel_Width(counter_current_text_00852a68,0)/2;
        previous_x=position.X-font->String_Pixel_Width(counter_previous_text_00852ab8,0)/2;
    } else {
        current_x=position.X;
        previous_x=position.X;
    }
    Rect current_area(current_x,position.Y,110,15);
    Rect previous_area(previous_x,position.Y,110,15);
    Rect screen_area=Merge_Counter_Areas(current_area,previous_area);
    Rect area=screen_area;
    area.X-=(unknown_surface_839954->Get_Width()-background->Get_Width())/2;
    area.Y-=(unknown_surface_839954->Get_Height()-background->Get_Height())/2;
    unknown_blit_49f3a0(*unknown_surface_839954,convert,*background,area,Point2D(0,0),screen_area,0,unknown_blit_flags,0,0,1000,0);
    Fancy_Text_Printf(counter_current_text_00852a68,unknown_surface_839954,
        &unknown_surface_839954->Get_Rect(),&position,
        unknown_color_scheme_663d30(counter_scheme_007d61e4,1),0,style);
}
