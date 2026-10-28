// void OptionsClass::Set_Voice_Volume(float volume, bool feedback) (0x005D8A70)
// @ref ??_C@_0BC@EMAN@VoiceVolume?5?$DN?5?$CFf?6?$AA@=007e86c4
// @ref ?Set_Volume@VoxClass@@SIXH@Z=00715ef0
// @ref __ftol=0077f110
// @ref __real@4@400d8000000000000000=007a77ac
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4006ff00000000000000=007a2f50
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/rules.hpp"
#include "shared/techno.hpp"
#include "shared/vox_class.hpp"

void OptionsClass::Set_Voice_Volume(float volume, bool feedback)
{
    VoiceVolume = volume < 1.0 ? volume : 1.0;
    VoxClass::Set_Volume((int)(VoiceVolume * 255.0));
    Audio_Global_Levels[1]->Volume.Set((int)(VoiceVolume * 16384.0f));
    if (feedback) {
        Voc_Play(Rules->GenericBeep, VoiceVolume, 0x2000, 0);
    }
    Debug_Printf("VoiceVolume = %f\n", VoiceVolume);
}
