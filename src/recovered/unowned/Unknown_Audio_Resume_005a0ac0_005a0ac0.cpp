// void Unknown_Audio_Resume_005a0ac0() (0x005A0AC0)
#include "shared/audio.hpp"
#include "shared/audio_pause.hpp"
// @ref ?unknown_audio_paused_a7101c@@3_NA=00a7101c
// @ref ?Audio_Streams_Release@@YAXXZ=00408150
// @ref ?Audio_Streams_Resume@@YAXXZ=00408210
// @ref ?Audio_Streams_Fade_In@@YAXXZ=004082f0
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0
// @ref ?unknown_tick_sound@@YAXXZ=007169f0

void Unknown_Audio_Resume_005a0ac0()
{
    if (unknown_audio_paused_a7101c) {
        Audio_Streams_Release();
        Audio_Streams_Resume();
        Audio_Streams_Fade_In();
        Audio_Global_Levels[7]->Volume.Set_Target(0x4000);
        Audio_Global_Levels[5]->Volume.Set_Target(0x4000);
        unknown_tick_sound();
        unknown_audio_paused_a7101c = false;
    }
}
