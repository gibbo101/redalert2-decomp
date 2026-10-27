// void SliderClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom) (0x00684D10, slot 19)
// Releasing the plus button steps up the value, the minus button down.
#include "shared/gadget.hpp"

void SliderClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom)
{
    if (flags & LEFTRELEASE) {
        if (&whom == PlusGadget) {
            Step(false);
        }
        if (&whom == MinusGadget) {
            Step(true);
        }
    }
}
