// int ControlClass::Action(unsigned flags, unsigned &key) (0x004834B0, slot 31)
// Reports the event as button key ID | 0x8000 (| 0x4000 for event 0x40 on a
// gadget that takes event 0x10), tells the peer, then runs GadgetClass::Action.
#include "shared/gadget.hpp"
// @ref ?Action@GadgetClass@@UAEHIAAI@Z=004cf220

int ControlClass::Action(unsigned flags, unsigned &key)
{
    if (flags) {
        if (ID) {
            key = ID | KN_BUTTON;
            if ((flags & 0x40) && (Flags & 0x10)) {
                key |= 0x4000;
            }
        } else {
            key = 0;
        }
    }
    if (Peer) {
        Peer->Peer_To_Peer(flags, key, *this);
    }
    return GadgetClass::Action(flags, key);
}
