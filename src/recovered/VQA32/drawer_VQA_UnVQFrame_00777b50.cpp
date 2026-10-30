// void __fastcall VQA_UnVQFrame(VQAHandleP *vqap, VQAFrameNode *frame) -- 0x00777B50
// Purpose: decodes a frame into the image buffer (or the buffer the event
// handler's LOCK returns) with UnVQ1, or UnVQ2 for frames with residual
// data; reports a newly completed codebook first and unlocks after.
#include "shared/vqa_player.hpp"

void __fastcall VQA_UnVQFrame(VQAHandleP *vqap, VQAFrameNode *frame)
{
    VQACBNode *codebk;
    VQAConfig *config;
    VQADrawer *drawer;

    config = &vqap->Config;
    drawer = &vqap->Drawer;
    codebk = frame->Codebook;

    if (!(drawer->Flags & VQADRWF_STEP)) {
        unsigned char *buf = 0;
        if (config->EventHandler != 0) {
            buf = (unsigned char *)config->EventHandler((VQAHandle *)vqap, VQAEVENT_LOCK, 0, 0);
        }
        if (buf == 0) {
            buf = drawer->ImageBuf;
        }
        if (buf == 0) {
            return;
        }

        unsigned char *buffer = buf + drawer->ScreenOffset;
        long blocksperrow = drawer->BlocksPerRow;
        long numrows = drawer->NumRows;
        unsigned char *codebook;
        unsigned char *pointers;

        if (frame->Flags & VQAFRMF_ALTPTR) {
            pointers = (unsigned char *)vqap->AltPtrBuffer;
        } else {
            pointers = frame->Pointers;
        }
        if (codebk->Flags & VQACBF_ALTPTR) {
            codebook = (unsigned char *)vqap->AltCBBuffer;
        } else {
            codebook = codebk->Buffer;
        }

        if (config->EventHandler != 0) {
            if (codebk->Flags & VQACBF_CBFULL) {
                codebk->Flags &= ~VQACBF_CBFULL;
                config->EventHandler((VQAHandle *)vqap, VQAEVENT_CODEBOOK, (int)codebook, codebk->CodebookSize);
            }
        }

        if (!(frame->Flags & VQAFRMF_RSDCOMP)) {
            vqap->UnVQ1(codebook, pointers, buffer, blocksperrow, numrows, drawer->ImageWidth);
        } else {
            vqap->UnVQ2(codebook, pointers, buffer, blocksperrow, numrows, drawer->ImageWidth);
        }

        if (config->EventHandler != 0) {
            config->EventHandler((VQAHandle *)vqap, VQAEVENT_UNLOCK, 0, 0);
        }
    }
}
