// void AbstractClass::Compute_CRC(WWCRCEngine &crc) const (0x004101B0)
// Adds the unique ID and the dirty flag to the CRC.
#include "shared/abstract.hpp"
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void AbstractClass::Compute_CRC(WWCRCEngine &crc) const
{
    crc(UniqueID);
    crc(Dirty);
}
