// LinkClass &DropListClass::Add_Tail(LinkClass &object) (0x004A4EF0, slot 4)
#include "shared/gadget.hpp"
// @ref ?Add_Tail@LinkClass@@UAEAAV1@AAV1@@Z=005390e0

LinkClass &DropListClass::Add_Tail(LinkClass &object)
{
    DropButton.Add_Tail(object);
    return EditClass::Add_Tail(object);
}
