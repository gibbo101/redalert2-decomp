// LinkClass *DropListClass::Remove() (0x004A4F30, slot 9)
#include "shared/gadget.hpp"
// @ref ?Remove@GadgetClass@@UAEPAVLinkClass@@XZ=004cf170

LinkClass *DropListClass::Remove()
{
    Collapse();
    DropButton.Remove();
    return EditClass::Remove();
}
