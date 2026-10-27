// SliderClass::~SliderClass() (0x006848C0)
// Deletes the plus and minus buttons.
#include "shared/gadget.hpp"
#include "shared/rect.hpp"
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ??_7SliderClass@@6B@=007a5754
// @ref ??_GSliderClass@@UAEPAXI@Z=0053ab40
// @ref ??_ESliderClass@@UAEPAXI@Z=0053ab40
// @ref ?Draw_Me@SliderClass@@UAEHH@Z=00684ca0
// @ref ?Action@SliderClass@@UAEHIAAI@Z=00684b10
// @ref ?Draw_Me@GaugeClass@@UAEHH@Z=004d0280
// @ref ?Action@GaugeClass@@UAEHIAAI@Z=004d0420
// @ref ?Pixel_To_Value@GaugeClass@@UAEHH@Z=004d01c0
// @ref ?Value_To_Pixel@GaugeClass@@UAEHH@Z=004d0240
// @ref ?Get_Value@GaugeClass@@UBEHXZ=004d0c80
// @ref ?Use_Thumb@GaugeClass@@UAEXH@Z=004d0c90
// @ref ?Thumb_Pixels@SliderClass@@UAEHXZ=0053aae0
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700
// @ref ?Make_Peer@ControlClass@@UAEXAAVGadgetClass@@@Z=00483510
// @ref ?Get_ID@ControlClass@@UBEIXZ=00483520

SliderClass::~SliderClass()
{
    if (PlusGadget != 0) {
        delete PlusGadget;
        PlusGadget = 0;
    }
    if (MinusGadget != 0) {
        delete MinusGadget;
        MinusGadget = 0;
    }
}
