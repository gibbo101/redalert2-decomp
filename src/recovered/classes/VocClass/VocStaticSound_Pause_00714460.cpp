// void VocStaticSound::Pause() (0x00714460): one more pause; pauses the
// handle's event (was UnknownOwner_00714460::unknown_bump_and_notify).
#include "shared/voc_static.hpp"
// @ref ?Audio_Event_Handle_Event@@YIPAUAudioEvent@@PAUAudioEventHandle@@@Z=00406140

void VocStaticSound::Pause()
{
    PauseCount++;
    AudioEvent *event = Audio_Event_Handle_Event(&Handle);
    if (event != 0) {
        Audio_Event_Pause(event);
    }
}
