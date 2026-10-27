// void AnimTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00426300)
#include "shared/anim_type.hpp"
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void AnimTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectTypeClass::Compute_CRC(crc);
    crc((long)Layer);
    crc(Normalized);
    crc(Flat);
    crc(Translucent);
    crc(Scorch);
    crc(Flamer);
    crc(Crater);
    crc(Sticky);
    crc(PingPong);
    crc(Reverse);
    crc(Shadow);
    crc((long)unknown_268);
    crc(Damage);
    crc(TiberiumChainReaction);
    crc((long)Rate);
    crc((long)Start);
    crc((long)LoopStart);
    crc((long)LoopEnd);
    crc((long)End);
    crc((long)StartSound);
    crc((long)StopSound);
    crc((long)DetailLevel);
    crc((long)TranslucencyDetailLevel);
    crc((long)RandomLoopDelayMin);
    crc((long)RandomLoopDelayMax);
    crc((long)Translucency);
    crc(Tiled);
}
