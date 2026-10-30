// int __fastcall VQA_Unknown_0077C6C0(VQAHandle *vqa, int start, int end, int iterations, int mode) -- 0x0077C6C0
// Purpose: VQA_SetLoop_Internal (TS): queues a loop over frames start..end.
// Mode 0 loops after the current loop, mode 1 jumps at the current loop's
// end (mode 2 when no loop is running), mode 2 seeks to the loop now.
// A negative iteration count loops forever. -23 for a bad range or mode.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C6C0(VQAHandle *vqa, int start, int end, int iterations, int mode)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    int rc = -1;

    if (start < vqap->NumFrames && end < vqap->NumFrames && start < end && mode >= VQALOOP_NORMAL
        && mode < VQALOOP_3) {
        if (iterations < 0) {
            iterations = -1;
        }
        if (vqap->LoopIterations == 0 && mode == VQALOOP_JUMP) {
            mode = VQALOOP_2;
        }
        if (mode != VQALOOP_2) {
            if (vqap->Flags & VQADATF_LOOPED) {
                if (mode == VQALOOP_NORMAL) {
                    vqap->LoopStartFrame1 = start;
                    vqap->LoopEndFrameNormal = end;
                    end = vqap->LoopEndFrameMode2;
                } else {
                    vqap->LoopStartFrame1 = start;
                    start = vqap->LoopStartFrame0;
                    vqap->LoopEndFrameNormal = vqap->LoopEndFrameMode2;
                }
            } else {
                vqap->LoopStartFrame2 = start;
                vqap->LoopEndFrame2 = end;
            }
        }
        vqap->LoopStartFrame0 = start;
        if (mode == VQALOOP_JUMP) {
            vqap->LoopIterationsJump = iterations;
            vqap->LoopEndFrameJump = end;
        } else {
            vqap->LoopIterations = iterations;
            if (mode == VQALOOP_2) {
                vqap->LoopEndFrameMode2 = end;
                vqap->StopFrame = end;
                if (VQA_Unknown_0077C2E0(vqa, start, 0) >= 0) {
                    rc = -1;
                } else {
                    rc = -23;
                }
            }
        }
    } else {
        rc = -23;
    }
    return rc;
}
