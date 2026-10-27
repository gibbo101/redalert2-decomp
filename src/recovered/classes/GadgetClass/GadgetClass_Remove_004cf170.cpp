// LinkClass *GadgetClass::Remove() (0x004CF170, slot 9)
// Drops the focus, then unlinks.
#include "shared/gadget.hpp"
// @ref ?Remove@LinkClass@@UAEPAV1@XZ=00539110

LinkClass *GadgetClass::Remove()
{
    Clear_Focus();
    return LinkClass::Remove();
}
