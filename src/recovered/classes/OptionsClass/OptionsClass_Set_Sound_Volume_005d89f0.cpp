// void OptionsClass::Set_Sound_Volume(float volume, bool feedback) (0x005D89F0)
// @ref ??_C@_0BC@CPNP@SoundVolume?5?$DN?5?$CFf?6?$AA@=007e86b0
// @ref __ftol=0077f110
// @ref __real@4@400d8000000000000000=007a77ac
// @ref __real@8@3fff8000000000000000=0079a708
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/rules.hpp"
#include "shared/techno.hpp"
#include "shared/vox_class.hpp"

void OptionsClass::Set_Sound_Volume(float volume, bool feedback)
{
    SoundVolume = volume < 1.0 ? volume : 1.0;
    Audio_Global_Levels[3]->Volume.Set((int)(SoundVolume * 16384.0f));
    if (feedback) {
        Voc_Play(Rules->GenericBeep, 1.0f, 0x2000, 0);
    }
    Debug_Printf("SoundVolume = %f\n", SoundVolume);
}
