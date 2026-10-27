// void AnimClass::Compute_CRC(WWCRCEngine &crc) const (0x00422DB0)
#include "shared/anim.hpp"
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70

void AnimClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    if (unknown_b4 != 0) {
        crc(unknown_b4->Fetch_ID());
    }
    crc((long)unknown_b8);
    crc((long)unknown_e4);
    crc((long)ZAdjust);
    crc((long)YSortAdjust);
    crc((long)LoopDelay);
    crc(unknown_168);
    crc((long)unknown_170);
    crc(unknown_174);
    crc((long)Loops);
    crc(unknown_176);
    crc(unknown_177);
    crc(unknown_17b);
    crc(unknown_17c);
    crc(unknown_17e);
}
