// void TechnoClass::unknown_slot198() (0x006D4060, slot 198)
// Plays a random sound from the type list VoiceAttack when sound is enabled.
#include "shared/techno.hpp"
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

void TechnoClass::unknown_slot198()
{
    if (unknown_sound_enabled_7d88d6) {
        if (unknown_slot32()->VoiceAttack.Count()) {
            DynamicVectorClass<int> &sounds = unknown_slot32()->VoiceAttack;
            unsigned random = unknown_random_839218();
            Voc_Play(sounds[random % sounds.Count()], 1.0f, 0x2000, 0);
        }
    }
}
