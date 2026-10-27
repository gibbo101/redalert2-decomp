// Aircraft slot133 move dispatcher00415FF0, independently verified26+6. Private diagnostic only.
#include "shared/aircraft.hpp"
// @ref ?unknown_416010@AircraftClass@@QAEHXZ=00416010
// @ref ?Move_Carryall_00416670@AircraftClass@@QAEHXZ=00416670
int AircraftClass::unknown_slot133()
{
    if (Type->Carryall) return Move_Carryall_00416670();
    return unknown_416010();
}
