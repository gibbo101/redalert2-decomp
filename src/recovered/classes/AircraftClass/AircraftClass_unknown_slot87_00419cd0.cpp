// void AircraftClass::unknown_slot87(CoordStruct const &source, bool forced, bool nokidding) (0x00419CD0, slot 87)
// When the current mission's control has flag +0x09, slot 261 with (0, 1);
// the arguments are not used.
#include "shared/aircraft.hpp"
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0

void AircraftClass::unknown_slot87(CoordStruct const &source, bool forced, bool nokidding)
{
    if (Control()->unknown_09) {
        unknown_slot261(0, 1);
    }
}
