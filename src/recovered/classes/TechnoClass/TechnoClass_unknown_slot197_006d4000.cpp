// void TechnoClass::unknown_slot197() (0x006D4000, slot 197)
// Plays a random sound from the type list VoiceMove when sound is enabled.
#include "shared/techno.hpp"
// @ref ?Unknown_00713DB0@@YIHHMHH@Z=00713db0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

void TechnoClass::unknown_slot197()
{
    if (unknown_sound_enabled_7d88d6) {
        if (unknown_slot32()->VoiceMove.Count()) {
            DynamicVectorClass<int> &sounds = unknown_slot32()->VoiceMove;
            unsigned random = unknown_random_839218();
            Unknown_00713DB0(sounds[random % sounds.Count()], 1.0f, 0x2000, 0);
        }
    }
}
