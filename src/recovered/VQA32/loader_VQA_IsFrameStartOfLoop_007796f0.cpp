// bool __fastcall VQA_IsFrameStartOfLoop(VQAHandleP *vqap, long framenum) -- 0x007796F0
// Purpose: frame 0 or the start frame of a loop in the LINF table.
#include "shared/vqa_player.hpp"

bool __fastcall VQA_IsFrameStartOfLoop(VQAHandleP *vqap, long framenum)
{
    int i;
    int count;
    VQALoopInfo::DATA *data;

    if (framenum == 0) {
        return true;
    }
    count = vqap->LoopInfo.Header.Count;
    if (count > 0 && ((vqap->LoopInfo.Header.Flags & 1) || (vqap->LoopInfo.Header.Flags & 2))) {
        data = vqap->LoopInfo.Data;
        for (i = 0; i < count; i++) {
            if (framenum == data[i].StartFrame) {
                return true;
            }
        }
    }
    return false;
}
