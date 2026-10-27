// EditClass::EditClass(unsigned id, wchar_t *text, int max_len, unsigned flags, int x, int y, int w, int h, int editflags) (0x004B2970)
// A width or height of -1 fits the text (or max_len wide characters) in the
// style's font.
#include "shared/gadget.hpp"
// @ref ??0ControlClass@@QAE@IHHHHI_N@Z=00483430
// @ref ??_7EditClass@@6B@=007a07bc
// @ref _wcslen=00783605
// @ref ??_C@_13DEHF@?$AAX?$AA?$AA@=007d6428
// @ref ?Gadget_Color_Scheme@@YAHXZ=004cefc0
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690
// @ref ?Get_Text@EditClass@@UAEPAGXZ=004a5550
// @ref ?Draw_Background@EditClass@@UAEXXZ=004b2c50
// @ref ?Draw_Text@EditClass@@UAEXPBG@Z=004b2c90
// @ref ?Handle_Key@EditClass@@UAE_NH@Z=004b2dd0
// @ref ?Action@EditClass@@UAEHIAAI@Z=004b2b40
// @ref ??_GEditClass@@UAEPAXI@Z=004a5780
// @ref ??_EEditClass@@UAEPAXI@Z=004a5780
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

EditClass::EditClass(unsigned id, wchar_t *text, int max_len, unsigned flags, int x, int y, int w, int h,
                     int editflags) :
    ControlClass(id, x, y, w, h, LEFTPRESS, false),
    TextFlags(flags & ~KEYBOARD)
{
    EditFlags = editflags;
    Set_Text(text, max_len);
    Color = Gadget_Color_Scheme();
    if (w == -1 || h == -1) {
        BitFontClass *font = Font_For_Style(flags);
        if (h == -1) {
            Height = font->Height + 1;
        }
        if (w == -1) {
            if (wcslen(String) > 0) {
                Width = font->String_Pixel_Width(String, 0) + 6;
            } else {
                Width = font->String_Pixel_Width(L"X", 0) * (MaxLength + 1) + 2;
            }
        }
    }
    IsReadOnly = 0;
}
