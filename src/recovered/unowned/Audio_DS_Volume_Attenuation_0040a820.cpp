// long __fastcall Audio_DS_Volume_Attenuation(int volume) -- 0x0040A820
// Purpose: maps a 0..255 volume to percent (volume * 100 / 256, clamped to
// 0..100) and returns its attenuation.
// @ref ?Audio_Attenuation@@3QBJB=007cce48
#include "shared/audio.hpp"

long __fastcall Audio_DS_Volume_Attenuation(int volume)
{
    int percent = volume * 100 / 256;
    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }
    return Audio_Attenuation[percent];
}
