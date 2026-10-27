// DropListClass::DropListClass(int id, wchar_t *text, int max_len, unsigned flags, int x, int y, int w, int h, void const *up, void const *down) (0x004A4DC0)
// An 18-pixel edit field (height then refit to the font) with the drop
// button at its right and an h-pixel list below the button's height.
#include "shared/gadget.hpp"
// @ref ??0EditClass@@QAE@IPAGHIHHHHH@Z=004b2970
// @ref ??0ShapeButtonClass@@QAE@IPBXHHHH_N@Z=00675060
// @ref ??0ListClass@@QAE@HHHHHIPBX0@Z=00539bf0
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ??_7DropListClass@@6B@=007a05e4
// @ref ??_GDropListClass@@UAEPAXI@Z=004a55a0
// @ref ??_EDropListClass@@UAEPAXI@Z=004a55a0
// @ref ?Set_Focus@EditClass@@UAEXXZ=004b2f20
// @ref ?Draw_Me@EditClass@@UAEHH@Z=004b2ac0
// @ref ?Action@EditClass@@UAEHIAAI@Z=004b2b40
// @ref ?Set_Text@EditClass@@UAEXPAGH@Z=004b2a90
// @ref ?Get_Text@EditClass@@UAEPAGXZ=004a5550
// @ref ?Draw_Background@EditClass@@UAEXXZ=004b2c50
// @ref ?Draw_Text@EditClass@@UAEXPBG@Z=004b2c90
// @ref ?Handle_Key@EditClass@@UAE_NH@Z=004b2dd0
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520
// @ref ??1ListClass@@UAE@XZ=00539fc0
// @ref ??1ShapeButtonClass@@UAE@XZ=006750f0
// @ref ??1EditClass@@UAE@XZ=004b2a60

DropListClass::DropListClass(int id, wchar_t *text, int max_len, unsigned flags, int x, int y, int w, int h,
                             void const *up, void const *down) :
    EditClass(id, text, max_len, flags, x, y, w, 18, 7),
    IsDropped(false),
    ListHeight(h),
    DropButton(0, down, x + w, y),
    List(0, x, y + ((short const *)down)[2], w + ((short const *)down)[1], h, flags, up, down)
{
    Height = Font_For_Style(flags)->Height + 1;
    List.Make_Peer(*this);
    DropButton.Make_Peer(*this);
}
