// int ControlClass::Draw_Me(int forced) (0x00483530, slot 27)
// Draws the peer first.
#include "shared/gadget.hpp"
// @ref ?Draw_Me@GadgetClass@@UAEHH@Z=004cf240

int ControlClass::Draw_Me(int forced)
{
    if (Peer) {
        Peer->Draw_Me();
    }
    return GadgetClass::Draw_Me(forced);
}
