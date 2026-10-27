// ToggleClass::ToggleClass(unsigned id, int x, int y, int w, int h) (0x006EB120)
// A sticky, released, switched-off button.
#include "shared/gadget.hpp"
// @ref ??0ControlClass@@QAE@IHHHHI_N@Z=00483430
// @ref ??_7ToggleClass@@6B@=007a0730
// @ref ??_GToggleClass@@UAEPAXI@Z=004a57c0
// @ref ??_EToggleClass@@UAEPAXI@Z=004a57c0
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520
// @ref ?Draw_Me@ControlClass@@UAEHH@Z=00483530

ToggleClass::ToggleClass(unsigned id, int x, int y, int w, int h) :
    ControlClass(id, x, y, w, h, LEFTPRESS | LEFTRELEASE, true),
    IsPressed(false),
    IsOn(false),
    ToggleType(0)
{
}
