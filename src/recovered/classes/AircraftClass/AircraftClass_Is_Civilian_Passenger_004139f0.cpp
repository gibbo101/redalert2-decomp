// Predicate in Aircraft.cpp (004139F0): a civilian infantry passenger with +5C1 clear.
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
bool __fastcall Is_Civilian_Passenger_004139F0(FootClass *passenger)
{
    if (!passenger) return false;
    InfantryClass *infantry = As_Infantry(passenger);
    if (!infantry) return false;
    if (!infantry->Type->Civilian) return false;
    if (infantry->unknown_5c1) return false;
    return true;
}
