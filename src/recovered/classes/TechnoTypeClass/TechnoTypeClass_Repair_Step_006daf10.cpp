// int TechnoTypeClass::Repair_Step() const (0x006DAF10)
// The rules repair step (slot 45).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int TechnoTypeClass::Repair_Step() const
{
    return Rules->unknown_1334;
}
