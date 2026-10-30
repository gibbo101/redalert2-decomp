// void __fastcall VQA_PauseAudio(VQAHandleP *vqap) -- 0x007764A0
// Purpose: pauses the audio handler (action 6), audio no longer playing.
#include "shared/vqa_player.hpp"

void __fastcall VQA_PauseAudio(VQAHandleP *vqap)
{
    vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_PAUSE, 0, 0);
    vqap->Audio.Flags &= ~VQAAUDF_ISPLAYING;
}
