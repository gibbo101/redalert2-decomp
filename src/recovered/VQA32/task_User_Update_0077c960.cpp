// long __fastcall User_Update(VQAHandle *vqa) -- 0x0077C960
// Purpose: shows the drawn frame: reports its loop events and chunks, runs
// the page flipper, and clears the frame's flags (or ends a held redraw).
#include "shared/vqa_player.hpp"

long __fastcall User_Update(VQAHandle *vqa)
{
    VQAHandleP *vqap;
    VQAFrameNode *curframe;
    VQADrawer *drawer;
    VQAConfig *config;
    long rc = 0;

    vqap = (VQAHandleP *)vqa;
    drawer = &vqap->Drawer;
    config = &vqap->Config;
    curframe = vqap->Flipper.CurFrame;

    if (config->EventHandler != 0) {
        if (curframe->Flags & VQAFRMF_LOOPED) {
            config->EventHandler((VQAHandle *)vqap, VQAEVENT_LOOPED, curframe->FrameNum, vqap->LoopID);
            curframe->Flags &= ~VQAFRMF_LOOPED;
        }
        if (curframe->Flags & VQAFRMF_LOOPJMP) {
            config->EventHandler((VQAHandle *)vqap, VQAEVENT_LOOPJUMP, curframe->FrameNum, vqap->LoopID);
            curframe->Flags &= ~VQAFRMF_LOOPJMP;
        }
        if (curframe->Flags & VQAFRMF_CHUNKS) {
            VQA_DispatchFrameChunks(vqap, curframe->FrameNum);
            curframe->Flags &= ~VQAFRMF_CHUNKS;
        }
    }

    rc = vqap->Page_Flip((VQAHandle *)vqap);
    vqap->Flipper.LastFrameNum = curframe->FrameNum;

    if (!(drawer->Flags & VQADRWF_HOLD)) {
        curframe->PrevFlags = curframe->Flags;
        curframe->Flags = 0;
    } else {
        if (drawer->Flags & VQADRWF_FORCEDRAW) {
            curframe->Flags |= VQAFRMF_11;
            drawer->Flags &= ~VQADRWF_FORCEDRAW;
        }
        drawer->Flags &= ~VQADRWF_HOLD;
    }
    return rc;
}
