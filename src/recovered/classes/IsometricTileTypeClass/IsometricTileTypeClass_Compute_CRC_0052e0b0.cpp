// void IsometricTileTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0052E0B0, slot 13)
#include "shared/isometric_tile_type.hpp"

void IsometricTileTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectTypeClass::Compute_CRC(crc);
    crc((long)ArrayIndex);
    crc((long)MarbleMadness);
    crc((long)NonMarbleMadness);
    crc((long)TileSetBaseID);
    crc((long)unknown_274.Count());
    if (unknown_28c != 0) {
        crc(unknown_28c->Fetch_ID());
    }
    crc((long)ToSnowTheater);
    crc((long)ToTemperateTheater);
    crc((long)AttachesTo);
    crc((long)ZAdjust);
    crc((long)Unused1);
    crc(unknown_2b0);
    crc(IsShadowCaster);
    crc((long)unknown_2b4);
    crc((long)unknown_2b8);
    crc((long)Unused2);
    crc((long)NumTileTypesInSet);
}
