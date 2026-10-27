// bool InfantryClass::unknown_5090a0() const (0x005090A0)
// The type's Deployer flag.
#include "shared/infantry.hpp"

bool InfantryClass::unknown_5090a0() const
{
    return Type->Deployer;
}
