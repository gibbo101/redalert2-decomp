// TextButtonClass::TextButtonClass(unsigned id, wchar_t const *text, int style, int x, int y, int w, int h, bool blackborder, bool bordered) (0x006E7240)
// A width or height of -1 is measured from the text and the current font.
#include "shared/gadget.hpp"
// @ref ??0ToggleClass@@QAE@IHHHH@Z=006eb120
// @ref ??_7TextButtonClass@@6B@=007ad764
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690
// @ref ?Draw_Background@TextButtonClass@@UAEXXZ=006e7390
// @ref ?Draw_Text@TextButtonClass@@UAEXPBG@Z=006e7460
// @ref ?Action@ToggleClass@@UAEHIAAI@Z=006eb180
// @ref ??_GTextButtonClass@@UAEPAXI@Z=006e7530
// @ref ??_ETextButtonClass@@UAEPAXI@Z=006e7530
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

TextButtonClass::TextButtonClass(unsigned id, wchar_t const *text, int style, int x, int y, int w, int h,
                                 bool blackborder, bool bordered) :
    ToggleClass(id, x, y, w, h),
    IsBlackBorder(blackborder),
    IsBordered(bordered),
    String(text),
    PrintFlags(style)
{
    if (w == -1 || h == -1) {
        BitFontClass *font = Font_For_Style(PrintFlags);
        if (w == -1) {
            Width = font->String_Pixel_Width(String, 0) + 8;
        }
        if (h == -1) {
            Height = font->Height + 2;
        }
    }
}
