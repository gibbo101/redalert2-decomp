// bool AircraftClass::unknown_slot21() const (0x0041B050, slot 21)
// For the two rules aircraft types (+0x434, +0x464): whether the locomotor
// is moving; otherwise FootClass's answer.
#include "shared/aircraft.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot21@FootClass@@UBE_NXZ=004cce70
// @ref ?_com_issue_error@@YGXJ@Z=00795940

bool AircraftClass::unknown_slot21() const
{
    if (Type == Rules->V3Rocket.Type || Type == Rules->DMisl.Type) {
        return Locomotor.Checked()->Is_Moving_Now() != 0;
    }
    return FootClass::unknown_slot21();
}
