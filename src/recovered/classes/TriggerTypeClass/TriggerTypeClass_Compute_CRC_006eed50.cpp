// void TriggerTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006EED50)
#include "shared/object.hpp"

void TriggerTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc(unknown_a4->Fetch_ID());
    if (Next != 0) {
        crc(Next->Fetch_ID());
    }
    if (Events != 0) {
        crc(Events->Fetch_ID());
    }
    if (Actions != 0) {
        crc(Actions->Fetch_ID());
    }
}
