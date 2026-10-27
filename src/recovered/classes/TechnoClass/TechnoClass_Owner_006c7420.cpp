// int TechnoClass::Owner() const (0x006C7420, slot 14)
// The owner number (+0x30 of the house).
#include "shared/techno.hpp"

int TechnoClass::Owner() const
{
    return House->ArrayIndex;
}
