// void Unknown_Audio_Pause_005a0b10() (0x005A0B10)
#include "shared/audio.hpp"
#include "shared/vox_speech.hpp"
#include "shared/audio_pause.hpp"
// @ref ?unknown_audio_paused_a7101c@@3_NA=00a7101c
// @ref ?Speech_Hold@@YAXXZ=00716980
// @ref ?Audio_Streams_Hold@@YAXXZ=00408120
// @ref ?Audio_Streams_Pause@@YAXXZ=00408190
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0

void Unknown_Audio_Pause_005a0b10()
{
    if (!unknown_audio_paused_a7101c) {
        Speech_Hold();
        Audio_Streams_Hold();
        Audio_Streams_Pause();
        Audio_Global_Levels[7]->Volume.Set_Target(0x2000);
        Audio_Global_Levels[5]->Volume.Set_Target(0x2000);
        unknown_audio_paused_a7101c = true;
    }
}
