// void ScoreClass::Play_Sound(char const *name, int volume) (0x006677F0)
// When a name is given and sound is available, walks Sounds while their
// names differ from it; nothing is played (the call is gone) and volume is
// unused. Input_Name and Presentation inline it.
#include "shared/score.hpp"
#include "shared/sound_available.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_check_406f30@@YAHXZ=00406f30

void ScoreClass::Play_Sound(char const *name, int volume)
{
    if (name != 0 && unknown_check_406f30()) {
        for (int index = 0; index < Sounds.Count(); index++) {
            char const *soundname = Sounds[index]->Name;
            if (_stricmp(name, soundname) == 0) {
                break;
            }
        }
    }
}
