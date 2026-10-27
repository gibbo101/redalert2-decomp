// LinkClass &DropListClass::Add_Head(LinkClass &object) (0x004A4F10, slot 5)
#include "shared/gadget.hpp"
// @ref ?Add_Head@LinkClass@@UAEAAV1@AAV1@@Z=005390c0

LinkClass &DropListClass::Add_Head(LinkClass &object)
{
    DropButton.Add_Head(object);
    return EditClass::Add_Head(object);
}
