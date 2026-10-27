#include "shared/infantry.hpp"
// Whether the current sequence blocks firing; called by TechnoClass at 0x006C9B87.
bool InfantryClass::Is_Busy_00509760() const
{
    return Is_Busy_Sequence_00509710(Sequence);
}
