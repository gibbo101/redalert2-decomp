// void ScriptTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00669170)
#include "shared/script.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void ScriptTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)MissionCount);
}
