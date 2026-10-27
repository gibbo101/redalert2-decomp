// void TaskForceClass::Compute_CRC(WWCRCEngine &crc) const (0x006B7110)
#include "shared/task_force.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void TaskForceClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)Group);
    crc((long)CountEntries);
}
