// bool InfantryClass::unknown_5090b0() const (0x005090B0)
// True when the type's UndeployDelay is set (above -1).
#include "shared/infantry.hpp"

bool InfantryClass::unknown_5090b0() const
{
    return Type->UndeployDelay > -1;
}
