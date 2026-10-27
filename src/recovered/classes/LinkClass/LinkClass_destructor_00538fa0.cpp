// LinkClass::~LinkClass() (0x00538FA0)
// Unlinks the node.
#include "shared/gadget.hpp"

LinkClass::~LinkClass()
{
    Remove();
}
