// int __fastcall VQA_Unknown_0077C640(VQAHandle *vqa, int id, int iterations, int mode) -- 0x0077C640
// Purpose: VQA_SetLoop (TS): plays loop `id` of the LINF table
// (VQA_SetLoop_Internal with its frame range) and records it as the
// current loop. -23 for an unknown loop.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C640(VQAHandle *vqa, int id, int iterations, int mode)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQAConfig *config = &vqap->Config;

    if (id >= vqap->LoopInfo.Header.Count || id < 0) {
        return -23;
    }
    if ((config->OptionFlags & VQAOPTF_AUDIO) && vqap->LoopInfo.Header.Count == 0) {
        return -23;
    }

    VQALoopInfo::DATA *data = &vqap->LoopInfo.Data[id];
    int start = data->StartFrame;
    int end = data->EndFrame;
    vqap->LoopID = id;
    int rc = VQA_Unknown_0077C6C0(vqa, start, end, iterations, mode);
    if (rc == -1) {
        vqap->LoopID = id;
    }
    return rc;
}
