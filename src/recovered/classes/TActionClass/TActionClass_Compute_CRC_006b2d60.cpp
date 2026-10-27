// void TActionClass::Compute_CRC(WWCRCEngine &crc) const (0x006B2D60)
#include "shared/object.hpp"

void TActionClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (Next != 0) {
        crc(Next->Fetch_ID());
    }
    crc((long)Type);
    if (unknown_30 != 0) {
        crc(unknown_30->Fetch_ID());
    }
    if (unknown_4c != 0) {
        crc(unknown_4c->Fetch_ID());
    }
    if (unknown_50 != 0) {
        crc(unknown_50->Fetch_ID());
    }
    crc((long)Data);
}
