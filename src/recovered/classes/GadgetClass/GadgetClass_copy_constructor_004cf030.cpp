// GadgetClass::GadgetClass(GadgetClass const &gadget) (0x004CF030)
// A copy of gadget's geometry and state, not linked into its list.
#include "shared/gadget.hpp"

GadgetClass::GadgetClass(GadgetClass const &gadget) :
    X(gadget.X),
    Y(gadget.Y),
    Width(gadget.Width),
    Height(gadget.Height),
    IsToRepaint(gadget.IsToRepaint),
    IsSticky(gadget.IsSticky),
    IsDisabled(gadget.IsDisabled),
    Flags(gadget.Flags)
{
}
