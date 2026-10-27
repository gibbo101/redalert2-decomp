// GaugeClass::GaugeClass(unsigned id, int x, int y, int w, int h) (0x004D00F0)
// A sticky 0..255 gauge, horizontal when wider than tall, with a thumb.
#include "shared/gadget.hpp"
// @ref ??0ControlClass@@QAE@IHHHHI_N@Z=00483430
// @ref ??_7GaugeClass@@6B@=007a18f4
// @ref ??_7TriColorGaugeClass@@6B@=007a19a0
// @ref ?Draw_Me@GaugeClass@@UAEHH@Z=004d0280
// @ref ?Action@GaugeClass@@UAEHIAAI@Z=004d0420
// @ref ?Draw_Thumb@GaugeClass@@UAEXXZ=004d0580
// @ref ?Draw_Me@TriColorGaugeClass@@UAEHH@Z=004d0730
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

GaugeClass::GaugeClass(unsigned id, int x, int y, int w, int h) :
    ControlClass(id, x, y, w, h, LEFTPRESS | LEFTHELD | LEFTRELEASE, true)
{
    Set_Maximum(255);
    Set_Value(0);
    HasThumb = true;
    IsHorizontal = (w > h);
    IsColorized = true;
    ClickDiff = 0;
}
