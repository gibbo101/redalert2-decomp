// GadgetClass::~GadgetClass() (0x004CF080)
// Drops the focus and every static reference to the gadget.
#include "shared/gadget.hpp"
// @ref ??1LinkClass@@UAE@XZ=00538fa0
// @ref ?StuckOn@GadgetClass@@2PAV1@A=00865ff0
// @ref ?LastList@GadgetClass@@2PAV1@A=00865ff4
// @ref ?Focused@GadgetClass@@2PAV1@A=00865ff8
// @ref ?MouseOver@GadgetClass@@2PAV1@A=00865ffc

GadgetClass::~GadgetClass()
{
    if (this == Focused) {
        Clear_Focus();
    }
    if (this == StuckOn) {
        StuckOn = 0;
    }
    if (this == LastList) {
        LastList = 0;
    }
    if (this == Focused) {
        Focused = 0;
    }
}
