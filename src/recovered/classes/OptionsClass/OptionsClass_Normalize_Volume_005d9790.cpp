// int OptionsClass::Normalize_Volume(int volume) (0x005D9790)
// A volume scaled by the sound volume (name after TS).
// @ref __ftol=0077f110
#include "shared/options.hpp"

int OptionsClass::Normalize_Volume(int volume)
{
    return volume * SoundVolume;
}
