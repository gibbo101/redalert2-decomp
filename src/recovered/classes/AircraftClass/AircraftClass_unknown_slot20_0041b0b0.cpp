// bool AircraftClass::unknown_slot20() const (0x0041B0B0, slot 20)
// For the two rules aircraft types (+0x434, +0x464): whether the locomotor
// is not moving; otherwise ObjectClass's answer.
#include "shared/aircraft.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot20@ObjectClass@@UBE_NXZ=005d53e0
// @ref ?_com_issue_error@@YGXJ@Z=00795940

bool AircraftClass::unknown_slot20() const
{
    if (Type == Rules->V3Rocket.Type || Type == Rules->DMisl.Type) {
        return !Locomotor.Checked()->Is_Moving_Now();
    }
    return FootClass::unknown_slot20();
}
