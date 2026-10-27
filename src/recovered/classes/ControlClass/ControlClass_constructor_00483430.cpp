// ControlClass::ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags, bool sticky) (0x00483430)
#include "shared/gadget.hpp"
// @ref ??0GadgetClass@@QAE@HHHHI_N@Z=004cefe0
// @ref ??_7ControlClass@@6B@=0079dea4

ControlClass::ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags, bool sticky) :
    GadgetClass(x, y, w, h, flags, sticky),
    ID(id),
    Peer(0)
{
}
