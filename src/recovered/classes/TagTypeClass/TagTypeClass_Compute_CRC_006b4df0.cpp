// void TagTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006B4DF0)
#include "shared/object.hpp"

void TagTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)Persistence);
}
