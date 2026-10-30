// long __fastcall PrimeBuffers(VQAHandleP *vqap) -- 0x007796A0
// Purpose: fills the frame buffers before playback; -9/-11 are not errors.
#include "shared/vqa_player.hpp"
// @ref ?VQA_LoadFrame@@YIJPAUVQAHandleP@@J@Z=00778680

long __fastcall PrimeBuffers(VQAHandleP *vqap)
{
    VQAConfig *config;
    long rc;
    long i;

    config = &vqap->Config;
    for (i = 0; i < config->NumFrameBufs; i++) {
        if ((rc = VQA_LoadFrame(vqap, 0x20)) == -1) {
            vqap->LoadedFrames++;
        } else if (rc != -9 && rc != -11) {
            return rc;
        }
    }
    return -1;
}
