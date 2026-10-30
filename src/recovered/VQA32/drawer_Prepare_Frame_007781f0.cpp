// void __fastcall Prepare_Frame(VQAHandleP *vqap) -- 0x007781F0
// Purpose: unpacks the current frame's compressed codebook, palette and
// vector pointers (into the alternate buffers when those are in use).
#include "shared/vqa_player.hpp"

void __fastcall Prepare_Frame(VQAHandleP *vqap)
{
    VQADrawer *drawer;
    VQAFrameNode *curframe;
    VQACBNode *codebook;

    drawer = &vqap->Drawer;
    curframe = drawer->CurFrame;
    codebook = curframe->Codebook;

    if (drawer->Flags & VQADRWF_STEP) {
        return;
    }

    if (codebook->Flags & VQACBF_CBCOMP) {
        void *cbbuffer = 0;
        if (vqap->AltBufferFlags & VQAABUFF_ALTCB) {
            cbbuffer = vqap->AltCBBuffer;
            codebook->Flags |= VQACBF_ALTPTR;
        } else {
            cbbuffer = codebook->Buffer;
        }
        codebook->CodebookSize = VQA_LCW_Uncompress((char *)(codebook->Buffer + codebook->CBOffset), (char *)cbbuffer,
                                                    vqap->CBBufferSize);
        codebook->Flags &= ~VQACBF_CBCOMP;
    }

    if (curframe->Flags & VQAFRMF_PALCOMP) {
        curframe->PaletteSize = VQA_LCW_Uncompress((char *)curframe->Palette + curframe->PalOffset, (char *)curframe->Palette,
                                                   vqap->Max_Pal_Size);
        curframe->Flags &= ~VQAFRMF_PALCOMP;
    }

    if (curframe->Flags & VQAFRMF_PTRCOMP) {
        void *ptrbuffer = 0;
        if (vqap->AltBufferFlags & VQAABUFF_ALTPTR) {
            ptrbuffer = vqap->AltPtrBuffer;
            curframe->Flags |= VQAFRMF_ALTPTR;
        } else {
            ptrbuffer = curframe->Pointers;
        }
        VQA_LCW_Uncompress((char *)curframe->Pointers + curframe->PtrOffset, (char *)ptrbuffer, vqap->PtrBufferSize);
        curframe->Flags &= ~VQAFRMF_PTRCOMP;
    }
}
