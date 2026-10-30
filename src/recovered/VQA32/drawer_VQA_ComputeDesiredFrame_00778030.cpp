// long __fastcall VQA_ComputeDesiredFrame(VQAHandleP *vqap, VQAConfig *config, VQADrawer *drawer,
//                                         VQAFrameNode *frame, unsigned long time) -- 0x00778030
// Purpose: converts the clock into the frame that should be on screen,
// stepping the clock back over a pending loop wrap, holding it on the
// current frame with NOSKIP, and committing the queued loop bounds once the
// drawer has crossed the wrap.
#include "shared/vqa_player.hpp"

long __fastcall VQA_ComputeDesiredFrame(VQAHandleP *vqap, VQAConfig *config, VQADrawer *drawer,
                                        VQAFrameNode *frame, unsigned long time)
{
    VQAHeader *header;
    long frame_rate;
    long frame_num;
    long result;
    bool crossed_loop;
    long loop_end;

    header = &vqap->Header;
    frame_rate = config->FrameRate;
    frame_num = frame->FrameNum;
    result = (time * frame_rate) / (int)VQA_TIMETICKS;
    if (drawer->Flags & VQADRWF_STEP) {
        result--;
    }

    crossed_loop = false;
    loop_end = vqap->LoopEndFrameMode2;
    if (vqap->Flags & VQADATF_LOOPED) {
        if (vqap->Flags & VQADATF_LOOPJMP) {
            loop_end = vqap->LoopEndFrame2;
        }
        while (true) {
            if ((config->DrawFlags & VQACFGF_NOSKIP) || result <= loop_end) {
                if (!(config->DrawFlags & VQACFGF_NOSKIP) || frame_num != vqap->LoopStartFrame0 || crossed_loop) {
                    break;
                }
            }
            int step_frames = vqap->LoopStartFrame0 - loop_end;
            step_frames--;
            VQA_StepTimer(vqap, VQA_TIMETICKS * step_frames / frame_rate);
            result = ((int)VQA_GetTime(vqap) * (int)frame_rate) / (int)VQA_TIMETICKS;
            crossed_loop = true;
            if (step_frames == 0) {
                break;
            }
        }
    }

    if (config->DrawFlags & VQACFGF_NOSKIP) {
        if (result > frame_num) {
            int step_frames = (frame_num - result);
            if (!(header->Flags & VQAHDF_AUDIO) || !(config->OptionFlags & VQAOPTF_AUDIO)) {
                VQA_StepTimer(vqap, VQA_TIMETICKS * step_frames / frame_rate);
            }
            result = frame_num;
            vqap->Flags |= VQADATF_FRAMESTALL;
        } else {
            vqap->Flags &= ~VQADATF_FRAMESTALL;
        }
    }

    if (crossed_loop) {
        if ((drawer->Flags & VQADRWF_STEP) && !(config->DrawFlags & VQACFGF_NOSKIP)) {
            result--;
            if (result < vqap->LoopStartFrame0) {
                result = loop_end;
            }
        }
        if (vqap->LoopEndFrameNormal != -1) {
            vqap->LoopStartFrame0 = vqap->LoopStartFrame1;
            vqap->LoopStartFrame1 = -1;
            vqap->LoopEndFrameMode2 = vqap->LoopEndFrameNormal;
            vqap->LoopEndFrameNormal = -1;
        }
        if (!(vqap->Flags & VQADATF_LOOPJMP)) {
            vqap->LoopStartFrame2 = vqap->LoopStartFrame0;
            vqap->LoopEndFrame2 = vqap->LoopEndFrameMode2;
        }
        vqap->Flags &= ~(VQADATF_LOOPED);
        vqap->Flags &= ~(VQADATF_LOOPJMP);
    }

    return result;
}
