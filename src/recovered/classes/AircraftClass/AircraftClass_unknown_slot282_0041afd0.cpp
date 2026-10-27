// bool AircraftClass::unknown_slot282() (0x0041AFD0, slot 282)
#include "shared/aircraft.hpp"
// @ref ?Unknown_006BA990@TeamClass@@QAE_NXZ=006ba990

bool AircraftClass::unknown_slot282()
{
    if (unknown_228 == 0 && unknown_32d && unknown_slot91() != 26 && unknown_slot91() != 27) {
        if ((Team == 0 && unknown_32c) || (Team != 0 && Team->Unknown_006BA990())) {
            return true;
        }
    }
    return false;
}
