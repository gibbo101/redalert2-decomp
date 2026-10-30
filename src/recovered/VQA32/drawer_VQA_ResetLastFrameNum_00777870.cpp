// long __fastcall VQA_ResetLastFrameNum(VQAHandle *vqa) -- 0x00777870
// Purpose: forgets the last drawn frame (-1) so playback progress after a
// seek is not measured against a frame from before it.
#include "shared/vqa_player.hpp"

long __fastcall VQA_ResetLastFrameNum(VQAHandle *vqa)
{
    VQAHandleP *vqap;
    VQADrawer *drawer;

    vqap = (VQAHandleP *)vqa;
    drawer = &vqap->Drawer;
    drawer->LastFrameNum = -1;
    return -1;
}
