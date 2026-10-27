// void ListClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom) (0x0053A4D0, slot 19)
// Arrow releases step the view; a scroll bar change moves it.
#include "shared/gadget.hpp"

void ListClass::Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom)
{
    if (flags & LEFTRELEASE) {
        if (&whom == &UpGadget) {
            Step(true);
        }
        if (&whom == &DownGadget) {
            Step(false);
        }
    }
    if (&whom == &ScrollGadget) {
        Set_View_Index(ScrollGadget.Get_Value());
    }
}
