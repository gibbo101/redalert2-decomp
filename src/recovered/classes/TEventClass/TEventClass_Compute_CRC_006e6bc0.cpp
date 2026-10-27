// void TEventClass::Compute_CRC(WWCRCEngine &crc) const (0x006E6BC0)
#include "shared/object.hpp"

void TEventClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (Next != 0) {
        crc(Next->Fetch_ID());
    }
    crc((long)Type);
    if (unknown_30 != 0) {
        crc(unknown_30->Fetch_ID());
    }
    crc((long)Data);
}
