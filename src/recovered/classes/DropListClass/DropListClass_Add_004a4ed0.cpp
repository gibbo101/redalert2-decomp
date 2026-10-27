// LinkClass &DropListClass::Add(LinkClass &object) (0x004A4ED0, slot 3)
#include "shared/gadget.hpp"
// @ref ?Add@LinkClass@@UAEAAV1@AAV1@@Z=005390a0

LinkClass &DropListClass::Add(LinkClass &object)
{
    DropButton.Add(object);
    return EditClass::Add(object);
}
