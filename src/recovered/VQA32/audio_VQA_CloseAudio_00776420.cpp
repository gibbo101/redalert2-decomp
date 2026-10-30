// void __fastcall VQA_CloseAudio(VQAHandleP *vqap) -- 0x00776420
// Purpose: stops playback if playing, closes the audio handler (action 3).
#include "shared/vqa_player.hpp"

void __fastcall VQA_CloseAudio(VQAHandleP *vqap)
{
    VQAAudio *audio = &vqap->Audio;

    if (audio->Flags & VQAAUDF_ISPLAYING) {
        VQA_StopAudio(vqap);
    }
    vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_CLOSE, 0, 0);
    if ((audio->Flags & VQAAUDF_MODLOCKED) == 1) {
        audio->Flags &= ~VQAAUDF_MODLOCKED;
    }
}
