// long __fastcall VQA_GetPaletteFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame) -- 0x007798C0
// Purpose: index and frame span of the PINF entry covering a frame.
#include "shared/vqa_player.hpp"

long __fastcall VQA_GetPaletteFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame)
{
    VQAPaletteInfo::DATA *data = vqap->PaletteInfo.Data;
    int count = vqap->PaletteInfo.Header.Count;
    int findex = 0;
    bool found = false;

    for (int i = 1; i < count; i++) {
        if (framenum >= data[i - 1].Frame) {
            if (framenum < data[i].Frame) {
                found = true;
                break;
            }
        }
        findex++;
    }
    if (!found) {
        findex = count - 1;
    }
    if (first_frame != 0) {
        *first_frame = data[findex].Frame;
    }
    if (last_frame != 0) {
        if (findex < count - 1) {
            *last_frame = data[findex + 1].Frame - 1;
        } else {
            *last_frame = vqap->NumFrames;
        }
    }
    return findex;
}
