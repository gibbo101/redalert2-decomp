// bool InfantryClass::unknown_509100() const (0x00509100)
// The type's DeployFire flag.
#include "shared/infantry.hpp"

bool InfantryClass::unknown_509100() const
{
    return Type->DeployFire;
}
