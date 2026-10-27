// ControlClass::ControlClass(ControlClass const &control) (0x00483480)
#include "shared/gadget.hpp"
// @ref ??0GadgetClass@@QAE@ABV0@@Z=004cf030

ControlClass::ControlClass(ControlClass const &control) :
    GadgetClass(control),
    ID(control.ID),
    Peer(control.Peer)
{
}
