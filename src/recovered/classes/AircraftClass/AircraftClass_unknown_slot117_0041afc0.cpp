// bool AircraftClass::unknown_slot117() (0x0041AFC0, slot 117)
// Unlocks (+0x5BA), then commences the queued mission.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot117@MissionClass@@UAE_NXZ=00594c50

bool AircraftClass::unknown_slot117()
{
    unknown_5ba = false;
    return MissionClass::unknown_slot117();
}
