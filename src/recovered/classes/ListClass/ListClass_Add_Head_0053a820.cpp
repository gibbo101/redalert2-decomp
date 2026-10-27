// LinkClass &ListClass::Add_Head(LinkClass &object) (0x0053A820, slot 5)
#include "shared/gadget.hpp"
// @ref ?Add_Head@LinkClass@@UAEAAV1@AAV1@@Z=005390c0

LinkClass &ListClass::Add_Head(LinkClass &object)
{
    if (IsScrollActive) {
        ScrollGadget.Add_Head(object);
        DownGadget.Add_Head(object);
        UpGadget.Add_Head(object);
    }
    return ControlClass::Add_Head(object);
}
