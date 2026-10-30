// long __fastcall VQA_GetCodebookFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame) -- 0x0077AC00
// Purpose: codebook group index of a frame from the CINF table (VQA_GetCodebookSize, the
// CINF size lookup of the partial codebook readers, is a static helper here).
#include "shared/vqa_player.hpp"

static long VQA_GetCodebookSize(VQAHandleP *vqap, long framenum)
{
    VQACodebookInfo *info = &vqap->CodebookInfo;
    VQACodebookInfo::DATA *data = info->Data;
    int count = info->Header.Count;
    bool found = false;
    int findex;

    for (int i = 0; i < count; i++) {
        if (data[i].Frame > framenum) {
            findex = i;
            found = true;
            break;
        }
    }
    if (found == false) {
        return 0;
    }
    return data[findex].Size;
}

long __fastcall VQA_GetCodebookFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame)
{
    VQACodebookInfo::DATA *data = vqap->CodebookInfo.Data;
    int count = vqap->CodebookInfo.Header.Count;
    unsigned int start_index;
    unsigned int end_index;
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
    if (findex == 0) {
        start_index = 0;
        end_index = 0;
    } else {
        start_index = findex - 1;
        end_index = findex;
    }
    if (first_frame != 0) {
        *first_frame = data[start_index].Frame;
    }
    if (last_frame != 0) {
        *last_frame = data[end_index].Frame - 1;
    }
    return findex;
}
