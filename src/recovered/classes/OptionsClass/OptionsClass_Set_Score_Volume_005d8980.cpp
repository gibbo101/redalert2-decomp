// void OptionsClass::Set_Score_Volume(float volume, bool feedback) (0x005D8980)
// @ref ??_C@_0BC@MLDC@ScoreVolume?5?$DN?5?$CFf?6?$AA@=007e869c
// @ref ?Set_Volume@ThemeClass@@QAEXH@Z=006e8590
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

void OptionsClass::Set_Score_Volume(float volume, bool feedback)
{
    ScoreVolume = volume < 1.0 ? volume : 1.0;
    Audio_Global_Levels[2]->Volume.Set((int)(ScoreVolume * 16384.0f));
    Theme.Set_Volume((int)(ScoreVolume * 255.0));
    Debug_Printf("ScoreVolume = %f\n", ScoreVolume);
}
