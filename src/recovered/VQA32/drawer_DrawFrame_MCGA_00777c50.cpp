// long __fastcall DrawFrame_MCGA(VQAHandle *vqa) -- 0x00777C50
// Purpose: the unbuffered frame drawer: selects and unpacks the next frame
// and hands it to the flipper (which decodes it), advancing unless held.
#include "shared/vqa_player.hpp"

long __fastcall DrawFrame_MCGA(VQAHandle *vqa)
{
    VQAHandleP *vqap;
    VQADrawer *drawer;
    VQAFrameNode *curframe;
    long rc;

    vqap = (VQAHandleP *)vqa;
    drawer = &vqap->Drawer;

    rc = Select_Frame(vqap);
    if (rc != -1) {
        return rc;
    }

    Prepare_Frame(vqap);
    curframe = drawer->CurFrame;
    vqap->Flipper.CurFrame = curframe;
    if (!(drawer->Flags & VQADRWF_HOLD)) {
        drawer->CurFrame = curframe->Next;
    }
    return -1;
}
