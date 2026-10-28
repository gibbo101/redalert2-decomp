// void VocStaticSound::Resume() (0x00714480): one pause fewer (not below 0);
// resumes the handle's event.
#include "shared/voc_static.hpp"
// @ref ?Audio_Event_Handle_Event@@YIPAUAudioEvent@@PAUAudioEventHandle@@@Z=00406140

void VocStaticSound::Resume()
{
    if (PauseCount != 0) {
        if (--PauseCount < 0) {
            PauseCount = 0;
        }
        AudioEvent *event = Audio_Event_Handle_Event(&Handle);
        if (event != 0) {
            Audio_Event_Resume(event);
        }
    }
}
