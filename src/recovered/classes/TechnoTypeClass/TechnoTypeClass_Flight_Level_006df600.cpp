// int TechnoTypeClass::Flight_Level() const (0x006DF600)
// FlightLevel=, or the rules default when unset (-1) (slot 47).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int TechnoTypeClass::Flight_Level() const
{
    if (FlightLevel == -1) {
        return Rules->unknown_6dc;
    }
    return FlightLevel;
}
