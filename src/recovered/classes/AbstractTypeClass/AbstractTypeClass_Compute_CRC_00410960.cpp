// void AbstractTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00410960)
// Adds the AbstractClass data, ID, Name and UIName label to the CRC.
#include "shared/abstract_type.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXPBD@Z=00493f90

void AbstractTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(ID);
    crc(Name);
    crc(UINameLabel);
}
