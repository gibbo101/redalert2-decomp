// void Audio_DS_Restart_Primary() -- 0x0040A870
// Purpose: keeps the primary buffer running: restores it when lost and
// plays it looping when not playing.
// @ref ?Audio_Primary_Buffer@@3PAUIDirectSoundBuffer@@A=008315b0
#include "shared/audio.hpp"

void Audio_DS_Restart_Primary()
{
    DWORD status;
    if (Audio_Primary_Buffer != 0) {
        Audio_Primary_Buffer->GetStatus(&status);
        if (status & DSBSTATUS_BUFFERLOST) {
            Audio_Primary_Buffer->Restore();
        }
        if (!(status & DSBSTATUS_PLAYING)) {
            Audio_Primary_Buffer->Play(0, 0, DSBPLAY_LOOPING);
        }
    }
}
