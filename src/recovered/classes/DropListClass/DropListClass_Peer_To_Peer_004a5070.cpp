// void DropListClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom) (0x004A5070, slot 19)
// The button toggles the list; picking from the list copies the item.
#include "shared/gadget.hpp"

void DropListClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom)
{
    if (&whom == &DropButton && (flags & LEFTRELEASE)) {
        if (IsDropped) {
            Collapse();
            key = ID | KN_BUTTON;
        } else {
            Expand();
        }
    }
    if (&whom == &List) {
        wcsncpy(String, List.Current_Item(), MaxLength);
        Flag_To_Redraw();
        key = ID | KN_BUTTON;
    }
}
