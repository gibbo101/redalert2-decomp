// ListClass::ListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) (0x00539BF0)
// The arrows sit inside the right edge (up at the top, down at the bottom)
// with the scroll bar between them; the bar is only linked in when needed.
#include "shared/gadget.hpp"
// @ref ??0ControlClass@@QAE@IHHHHI_N@Z=00483430
// @ref ??0ShapeButtonClass@@QAE@IPBXHHHH_N@Z=00675060
// @ref ??0SliderClass@@QAE@IHHHHH@Z=006846e0
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ??_7ListClass@@6B@=007a5644
// @ref ??_7?$DynamicVectorClass@PAG@@6B@=007a5714
// @ref ??_7?$VectorClass@PAG@@6B@=007a5734
// @ref ?Set_Position@ListClass@@UAEXHH@Z=00539f30
// @ref ?Count@ListClass@@UBEHXZ=0047d710
// @ref ?Draw_Entry@ListClass@@UAEXHHHHH@Z=0053a6e0
// @ref ??_GListClass@@UAEPAXI@Z=0053aa20
// @ref ??_EListClass@@UAEPAXI@Z=0053aa20
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

ListClass::ListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) :
    ControlClass(id, x, y, w, h, LEFTPRESS | LEFTRELEASE | KEYBOARD, false),
    UpGadget(0, up, x + w, y),
    DownGadget(0, down, x + w, y + h),
    ScrollGadget(0, x + w, y, 0, h, true)
{
    UpGadget.X -= UpGadget.Width;
    DownGadget.X -= DownGadget.Width;
    DownGadget.Y -= DownGadget.Height;
    ScrollGadget.X -= (UpGadget.Width > DownGadget.Width) ? UpGadget.Width : DownGadget.Width;
    ScrollGadget.Y = Y + UpGadget.Height;
    ScrollGadget.Height -= UpGadget.Height + DownGadget.Height;
    ScrollGadget.Width = (UpGadget.Width > DownGadget.Width) ? UpGadget.Width : DownGadget.Width;

    TextFlags = flags;
    IsScrollActive = false;
    Tabs = 0;
    SelectedIndex = 0;
    CurrentTopIndex = 0;
    LineHeight = Font_For_Style(flags)->Height - 1;
    LineCount = (h - 1) / LineHeight;
}
