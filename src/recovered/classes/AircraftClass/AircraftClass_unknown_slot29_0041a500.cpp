// int AircraftClass::unknown_slot29() const (0x0041A500, slot 29)
// The locomotor's layer.
#include "shared/aircraft.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

int AircraftClass::unknown_slot29() const
{
    return Locomotor.Checked()->Layer();
}
