// void ScriptClass::Compute_CRC(WWCRCEngine &crc) const (0x00668850)
#include "shared/script.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void ScriptClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)CurrentMission);
}
