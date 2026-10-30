// int __fastcall VQA_Unknown_0077C440(VQAHandle *vqa, void (*unvq1)(), void (*unvq2)()) -- 0x0077C440
// Purpose: VQA_SetUnVQ (TS): installs caller-supplied UnVQ decoders; a null
// pointer installs UnVQ_Nop.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C440(VQAHandle *vqa, void (*unvq1)(), void (*unvq2)())
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;

    if (unvq1 != 0) {
        vqap->UnVQ1 = (UNVQ_FUNC)unvq1;
    } else {
        vqap->UnVQ1 = UnVQ_Nop;
    }
    if (unvq2 != 0) {
        vqap->UnVQ2 = (UNVQ_FUNC)unvq2;
    } else {
        vqap->UnVQ2 = UnVQ_Nop;
    }
    return -1;
}
