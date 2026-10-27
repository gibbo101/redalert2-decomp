// void GadgetClass::Draw_All(bool forced) (0x004CF260, slot 11)
// Draws this gadget and every following one.
#include "shared/gadget.hpp"

void GadgetClass::Draw_All(bool forced)
{
    for (GadgetClass *gadget = this; gadget != 0; gadget = (GadgetClass *)gadget->Get_Next()) {
        gadget->Draw_Me(forced);
    }
}
