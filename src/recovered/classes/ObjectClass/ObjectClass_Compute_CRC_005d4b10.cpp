// void ObjectClass::Compute_CRC(WWCRCEngine &crc) const (0x005D4B10)
#include "shared/object_type.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

void ObjectClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (unknown_30 != 0) {
        crc(unknown_30->Fetch_ID());
    }
    if (unknown_34 != 0) {
        crc(unknown_34->Fetch_ID());
    }
    crc((long)Strength);
    crc(unknown_74);
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        crc(unknown_75);
        crc(unknown_77);
    }
    crc(unknown_76);
    crc(unknown_78);
    crc(unknown_79);
    crc(unknown_7a);
    crc(unknown_7c);
    crc(unknown_7d);
    crc((long)Coord.X);
    crc((long)Coord.Y);
    crc((long)Coord.Z);
}
