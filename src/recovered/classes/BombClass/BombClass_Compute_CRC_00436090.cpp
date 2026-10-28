// void BombClass::Compute_CRC(WWCRCEngine &crc) const (0x00436090)
#include "shared/object.hpp"
#include "shared/wwcrc_engine.hpp"
#include "shared/house.hpp"
#include "shared/techno.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0

void BombClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (unknown_28 != 0) {
        crc(unknown_28->Fetch_ID());
    }
    if (Owner != 0) {
        crc(Owner->Fetch_ID());
    }
    if (Target != 0) {
        crc(Target->Fetch_ID());
    }
    crc(unknown_58);
}
