// void TriggerClass::Compute_CRC(WWCRCEngine &crc) const (0x006EDA00)
#include "shared/object.hpp"

void TriggerClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(Class->Fetch_ID());
    if (Next != 0) {
        crc(Next->Fetch_ID());
    }
    crc((char)unknown_2c);
    crc((char)IsEnabled);
    crc(Timer.Value());
    crc((long)Events);
}
