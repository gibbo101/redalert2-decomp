// long __fastcall VQA_LargestLoop(VQAHandleP *vqap, long streamsize) -- 0x0077CA70
// Purpose: the size in bytes of the largest loop of the LINF table (from
// the FINF frame offsets; a loop ending at the last frame ends at
// streamsize when that is known).
#include "shared/vqa_player.hpp"

long __fastcall VQA_LargestLoop(VQAHandleP *vqap, long streamsize)
{
    VQAInfoHeader *infohdr = &vqap->LoopInfo.Header;
    long largest = 0;
    int count = infohdr->Count;

    for (int i = 0; i < count; i++) {
        VQALoopInfo::DATA *data = &vqap->LoopInfo.Data[i];
        int start = data->StartFrame;
        int stop = data->EndFrame;
        long start_offset;
        long end_offset;
        long loopsize = 0;

        if (stop != vqap->NumFrames - 1) {
            end_offset = VQAFRAME_OFFSET(vqap->Foff[stop + 1]);
            start_offset = VQAFRAME_OFFSET(vqap->Foff[start]);
            loopsize = end_offset - start_offset;
        } else if (streamsize > 0) {
            end_offset = streamsize;
            start_offset = VQAFRAME_OFFSET(vqap->Foff[start]);
            loopsize = end_offset - start_offset;
        } else {
            end_offset = VQAFRAME_OFFSET(vqap->Foff[stop]);
            start_offset = VQAFRAME_OFFSET(vqap->Foff[start]);
            loopsize = end_offset - start_offset;
        }
        if (loopsize > largest) {
            largest = loopsize;
        }
    }
    return largest;
}
