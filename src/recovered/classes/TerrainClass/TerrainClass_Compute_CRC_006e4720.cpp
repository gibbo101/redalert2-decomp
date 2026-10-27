// void TerrainClass::Compute_CRC(WWCRCEngine &crc) const (0x006E4720)
#include "shared/terrain.hpp"
// @ref ?Compute_CRC@ObjectClass@@UBEXAAVWWCRCEngine@@@Z=005d4b10
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void TerrainClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    crc((long)Class->Kind_Of());
    crc(Class->Fetch_ID());
    crc(unknown_b4);
    crc(unknown_b5);
    crc((long)unknown_b8.X);
    crc((long)unknown_b8.Y);
}
