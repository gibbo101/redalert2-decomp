// LinkClass &LinkClass::operator=(LinkClass &link) (0x00539000)
// Leaves the current list and joins link's.
#include "shared/gadget.hpp"

LinkClass &LinkClass::operator=(LinkClass &link)
{
    if (&link != this) {
        Remove();
        Add(link);
    }
    return *this;
}
