// LinkClass::LinkClass(LinkClass &link) (0x00538F60)
// A new node added after link in link's list.
#include "shared/gadget.hpp"
// @ref ??_7LinkClass@@6B@=007a18b4

LinkClass::LinkClass(LinkClass &link) :
    Next(0),
    Prev(0)
{
    Add(link);
}
