// void VoxelAnimClass::Compute_CRC(WWCRCEngine &crc) const (0x0070DE70)
#include "shared/voxel_anim.hpp"
// @ref ?Compute_CRC@ObjectClass@@UBEXAAVWWCRCEngine@@@Z=005d4b10
// @ref ??RWWCRCEngine@@QAEXD@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void VoxelAnimClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    crc((long)unknown_e8);
    crc(Class->Fetch_ID());
    if (unknown_f0 != 0) {
        crc(unknown_f0->Fetch_ID());
    }
    crc(unknown_f4->Fetch_ID());
    crc((char)unknown_f8);
    crc((char)unknown_124);
    crc((long)unknown_128);
}
