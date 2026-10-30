// void __fastcall VQA_StopAudio(VQAHandleP *vqap) -- 0x007764C0
// Purpose: stops the audio handler (action 7), audio no longer playing.
#include "shared/vqa_player.hpp"

void __fastcall VQA_StopAudio(VQAHandleP *vqap)
{
    vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_STOP, 0, 0);
    vqap->Audio.Flags &= ~VQAAUDF_ISPLAYING;
}
