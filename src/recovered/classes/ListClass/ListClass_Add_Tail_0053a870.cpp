// LinkClass &ListClass::Add_Tail(LinkClass &object) (0x0053A870, slot 4)
#include "shared/gadget.hpp"
// @ref ?Add_Tail@LinkClass@@UAEAAV1@AAV1@@Z=005390e0

LinkClass &ListClass::Add_Tail(LinkClass &object)
{
    ControlClass::Add_Tail(object);
    if (IsScrollActive) {
        UpGadget.Add_Tail(object);
        DownGadget.Add_Tail(object);
        ScrollGadget.Add_Tail(object);
    }
    return Head_Of_List();
}
