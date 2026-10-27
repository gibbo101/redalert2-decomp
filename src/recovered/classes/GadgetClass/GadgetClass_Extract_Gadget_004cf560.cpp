// ControlClass *GadgetClass::Extract_Gadget(unsigned id) (0x004CF560, slot 13)
// The gadget of the list (from this one) with this ID; null for ID 0.
#include "shared/gadget.hpp"

ControlClass *GadgetClass::Extract_Gadget(unsigned id)
{
    GadgetClass *gadget = this;
    if (id != 0) {
        while (gadget != 0) {
            if (gadget->Get_ID() == id) {
                return (ControlClass *)gadget;
            }
            gadget = (GadgetClass *)gadget->Get_Next();
        }
    }
    return 0;
}
