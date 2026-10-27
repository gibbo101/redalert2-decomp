// WarheadTypeClass scalar deleting destructor (0x00721090): compiler generated,
// with the destructor expanded inline. The destructor itself (0x007203D0) is
// defined here: its frozen inventory bound is split at 0x0072043B, so it is
// bound by reference until the bound is refined.
#include "shared/warhead_type.hpp"

WarheadTypeClass::~WarheadTypeClass()
{
    Unknown_006ECB90(this, true);
    unknown_WarheadTypeClass_list_00839b00.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
}
