// ?Compute_CRC@AITriggerTypeClass@@UBEXAAVWWCRCEngine@@@Z (0x0041C850)
// AbstractTypeClass part and the trigger fields; the comparator only for condition types 0, 1, 4 and 7.
#include "shared/ai_trigger_type.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void AITriggerTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)ConditionType);
    crc((long)unknown_9c);
    crc((long)unknown_a0);
    crc((long)unknown_a8);
    crc((long)unknown_b0);
    switch (ConditionType) {
    case 0:
    case 1:
    case 4:
    case 7:
        crc(((long const *)Comparator)[0]);
        crc(((long const *)Comparator)[1]);
        break;
    }
    crc(Weight);
    crc(MinWeight);
    crc(MaxWeight);
    crc(unknown_d0);
    crc(unknown_d2);
    crc(unknown_d3);
    crc(unknown_d4);
    crc((long)unknown_ac);
    crc(unknown_d1);
}
