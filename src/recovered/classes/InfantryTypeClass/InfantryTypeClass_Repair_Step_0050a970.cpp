// int InfantryTypeClass::Repair_Step() const (0x0050A970)
// The rules value at +0x1340.
#include "shared/infantry_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int InfantryTypeClass::Repair_Step() const
{
    // Rules +0x1340 is not yet a named field of shared/object.hpp's rules view.
    return Rules->unknown_1340;
}
