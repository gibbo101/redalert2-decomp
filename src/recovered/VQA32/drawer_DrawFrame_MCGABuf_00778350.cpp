// long __fastcall DrawFrame_MCGABuf(VQAHandle *vqa) -- 0x00778350
// Purpose: the buffered frame drawer: selects, unpacks and decodes the next
// frame into the image buffer and hands it to the flipper.
#include "shared/vqa_player.hpp"

long __fastcall DrawFrame_MCGABuf(VQAHandle *vqa)
{
    long rc;
    VQAHandleP *vqap;
    VQADrawer *drawer;
    VQAFrameNode *curframe;

    vqap = (VQAHandleP *)vqa;
    drawer = &vqap->Drawer;

    rc = Select_Frame(vqap);
    if (rc != -1) {
        return rc;
    }

    Prepare_Frame(vqap);
    curframe = drawer->CurFrame;
    VQA_UnVQFrame(vqap, curframe);
    vqap->Flipper.CurFrame = curframe;
    if ((drawer->Flags & VQADRWF_HOLD) == 0) {
        drawer->CurFrame = curframe->Next;
    }
    return -1;
}
