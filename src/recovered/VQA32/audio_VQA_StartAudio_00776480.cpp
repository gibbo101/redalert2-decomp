// void __fastcall VQA_StartAudio(VQAHandleP *vqap) -- 0x00776480
// Purpose: starts the audio handler (action 4) and marks audio playing.
#include "shared/vqa_player.hpp"

void __fastcall VQA_StartAudio(VQAHandleP *vqap)
{
    VQAAudio *audio = &vqap->Audio;

    vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_START, 0, 0);
    audio->Flags |= VQAAUDF_ISPLAYING;
}
