// long __fastcall VQA_NumFramesWithPalettes(VQAHandleP *vqap) -- 0x0077CA30
// Purpose: counts the frames whose FINF entry carries a palette.
#include "shared/vqa_player.hpp"

long __fastcall VQA_NumFramesWithPalettes(VQAHandleP *vqap)
{
    long num = 0;

    for (int i = 0; i < vqap->NumFrames; i++) {
        if (vqap->Foff[i] & VQAFINF_PAL) {
            num++;
        }
    }
    return num;
}
