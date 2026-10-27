// LinkClass *ListClass::Remove() (0x0053A8C0, slot 9)
#include "shared/gadget.hpp"
// @ref ?Remove@GadgetClass@@UAEPAVLinkClass@@XZ=004cf170

LinkClass *ListClass::Remove()
{
    if (IsScrollActive) {
        ScrollGadget.Remove();
        DownGadget.Remove();
        UpGadget.Remove();
    }
    return ControlClass::Remove();
}
