// EditClass::~EditClass() (0x004B2A60)
#include "shared/gadget.hpp"
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ?Has_Focus@GadgetClass@@UAE_NXZ=004cf630
// @ref ?Clear_Focus@GadgetClass@@UAEXXZ=004cf610

EditClass::~EditClass()
{
    if (Has_Focus()) {
        Clear_Focus();
    }
}
