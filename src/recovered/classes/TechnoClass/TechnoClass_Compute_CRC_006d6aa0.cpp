// void TechnoClass::Compute_CRC(WWCRCEngine &crc) const (0x006D6AA0, slot 13)
// RadioClass's part, then the techno's state: indices, factors, timers'
// remaining time, flags (the player-visibility flags only in game modes 0 and
// 5), the height level, and the +0x3A8 objects (with their +0x390 values)
// and +0x3C0 objects by ID.
#include "shared/techno.hpp"
// @ref ?Compute_CRC@RadioClass@@UBEXAAVWWCRCEngine@@@Z=00636bf0
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXM@Z=00493f50
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

extern int unknown_game_mode_a3d298;    // 0x00A3D298

void TechnoClass::Compute_CRC(WWCRCEngine &crc) const
{
    RadioClass::Compute_CRC(crc);
    crc((long)unknown_1ac);
    crc((long)unknown_114);
    crc(unknown_120);
    crc(unknown_128);
    crc(unknown_130.Value());
    crc((long)unknown_1a8);
    crc((long)unknown_1b8);
    crc(unknown_1d4.Value());
    crc(unknown_1e0);
    crc(unknown_1e4);
    crc((long)unknown_1f4);
    crc(unknown_240);
    crc(unknown_244.Value());
    crc((long)unknown_254);
    crc(unknown_194.Value());
    crc((long)unknown_258);
    crc(unknown_280);
    crc(unknown_284);
    crc(unknown_288);
    crc(unknown_28c);
    crc(unknown_325);
    crc(unknown_327);
    crc(unknown_328);
    crc(unknown_329);
    crc(unknown_32a);
    crc(unknown_32b);
    crc(unknown_32c);
    crc(unknown_32d);
    crc(unknown_370);
    crc(unknown_371);
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        crc(unknown_372);
        crc(unknown_373);
        crc(unknown_374);
    }
    crc(unknown_375);
    crc((long)unknown_3fc);
    crc((long)unknown_376);
    crc((long)unknown_377);
    crc(unknown_378);
    int count = unknown_3a8.Count();
    crc((long)count);
    for (int index = 0; index < count; index++) {
        AbstractClass *object = unknown_3a8[index];
        int value = unknown_390[index];
        crc(object->Fetch_ID());
        crc((long)value);
    }
    count = unknown_3c0.Count();
    crc((long)count);
    for (index = 0; index < count; index++) {
        crc(unknown_3c0[index]->Fetch_ID());
    }
}
