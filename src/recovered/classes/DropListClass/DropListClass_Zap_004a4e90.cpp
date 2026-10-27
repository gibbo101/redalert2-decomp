// void DropListClass::Zap() (0x004A4E90, slot 8)
#include "shared/gadget.hpp"
// @ref ?Zap@LinkClass@@UAEXXZ=00538ff0

void DropListClass::Zap()
{
    Collapse();
    List.Zap();
    DropButton.Zap();
    EditClass::Zap();
}
