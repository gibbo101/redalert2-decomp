// void MissionClass::Compute_CRC(WWCRCEngine &crc) const (0x00595040, slot 13)
#include "shared/mission.hpp"
// @ref ?Compute_CRC@ObjectClass@@UBEXAAVWWCRCEngine@@@Z=005d4b10

void MissionClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    crc((long)Mission);
    crc((long)SuspendedMission);
    crc((long)MissionQueue);
    crc((long)unknown_a8);
    crc((long)Timer.Value());
    crc((long)unknown_ac);
}
