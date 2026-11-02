// SideClass::~SideClass() (0x0067AED0)
// Leaves the dying side's notice lists and Sides; ~TypeList and ~AbstractTypeClass follow. Defined
// here, not inline: the scalar deleting destructor 0x0067B1F0 expands this body.
#include "shared/side.hpp"

SideClass::~SideClass()
{
    Unknown_006ECB90(this, true);
    Sides.Delete(this);
}
