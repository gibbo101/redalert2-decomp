// ShapeButtonClass::ShapeButtonClass() (0x00675020)
#include "shared/gadget.hpp"
// @ref ??0ToggleClass@@QAE@IHHHH@Z=006eb120
// @ref ??_7ShapeButtonClass@@6B@=007a06a0
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?Draw_Me@ShapeButtonClass@@UAEHH@Z=006751e0
// @ref ?Action@ToggleClass@@UAEHIAAI@Z=006eb180
// @ref ??_GShapeButtonClass@@UAEPAXI@Z=004a57a0
// @ref ??_EShapeButtonClass@@UAEPAXI@Z=004a57a0
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

ShapeButtonClass::ShapeButtonClass() :
    ToggleClass(0, 0, 0, 0, 0),
    unknown_34(false),
    unknown_38(0),
    unknown_3c(0),
    unknown_40(false),
    OffsetX(0),
    OffsetY(0),
    unknown_4c(false),
    unknown_50(unknown_drawer_8323c4),
    unknown_55(false),
    IsShapeAllocated(false)
{
}
