#include "shared/task_force.hpp"
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
void TaskForceEntryStruct::Compute_CRC_004B4930(WWCRCEngine &crc) const
{
    crc((long)Amount);
    if(Type) {
        crc((long)Type->Kind_Of());
        crc(Type->Fetch_ID());
    }
}
