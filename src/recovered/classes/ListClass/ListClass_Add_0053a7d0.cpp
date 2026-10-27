// LinkClass &ListClass::Add(LinkClass &object) (0x0053A7D0, slot 3)
// The scroll parts follow the list.
#include "shared/gadget.hpp"
// @ref ?Add@LinkClass@@UAEAAV1@AAV1@@Z=005390a0

LinkClass &ListClass::Add(LinkClass &object)
{
    if (IsScrollActive) {
        ScrollGadget.Add(object);
        DownGadget.Add(object);
        UpGadget.Add(object);
    }
    return ControlClass::Add(object);
}
