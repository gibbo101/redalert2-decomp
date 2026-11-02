// TextLabelClass::TextLabelClass(wchar_t const *text, int x, int y, int color, unsigned style) (0x006F15C0)
// A one-pixel gadget at x, y printing text in colour scheme color with print style style; the
// width is the surface's (PixWidth -1) and the text is shown at once (no reveal).
#include "shared/text_label.hpp"
// @ref ??0GadgetClass@@QAE@HHHHI_N@Z=004cefe0
// @ref ??_7TextLabelClass@@6B@=007adccc
// @ref ?Draw_Me@TextLabelClass@@UAEHH@Z=006f1620
// @ref ?Set_Text@TextLabelClass@@UAEXPBG@Z=006f17e0
// @ref ??_GTextLabelClass@@UAEPAXI@Z=006f17f0
// @ref ??_ETextLabelClass@@UAEPAXI@Z=006f17f0
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Get_ID@GadgetClass@@UBEIXZ=0049ecd0

TextLabelClass::TextLabelClass(wchar_t const *text, int x, int y, int color, unsigned style) :
    GadgetClass(x, y, 1, 1, 0, 0),
    UserData1(0),
    UserData2(0),
    Style(style),
    Text(text),
    Color(color),
    PixWidth(-1),
    Scroll(0),
    IsHidden(false),
    IsRevealed(false),
    RevealCount(0),
    RevealTime(0)
{
}
