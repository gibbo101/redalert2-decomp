// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// long __fastcall Load_CBPZ(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B140
// From ra2-decomp (YR 0x007C1F30).
// Purpose: appends a compressed partial codebook at the top of the codebook buffer; completes it at the group size.
#include "shared/vqa_player.hpp"

long __fastcall Load_CBPZ(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAConfig *config;
    VQALoader *loader;
    VQACBNode *curcb;
    void *buffer;
    unsigned long padsize;
    long groupsize;
    int cbfull;

    padsize = PADSIZE(iffsize);
    config = &vqap->Config;
    loader = &vqap->Loader;
    curcb = loader->CurCB;
    groupsize = vqap->Header.Groupsize;

    if (loader->PartialCBSize == 0) {
        if (groupsize != 0) {
            loader->CBSize = PADSIZE(groupsize) + groupsize * padsize;
        } else {
            loader->CBSize = VQA_GetCodebookSize(vqap, loader->CurFrameNum);
        }
        if (!(vqap->AltBufferFlags & VQAABUFF_ALTCB)) {
            curcb->CBOffset = vqap->Max_CB_Size - loader->CBSize;
        } else {
            curcb->CBOffset = 0;
        }
    }

    buffer = curcb->Buffer + curcb->CBOffset;
    buffer = (char *)buffer + loader->PartialCBSize;

    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, padsize)) {
        return -4;
    }

    loader->PartialCBSize += iffsize;
    loader->NumPartialCB++;
    cbfull = false;

    if (groupsize != 0) {
        if (loader->NumPartialCB == groupsize) {
            cbfull = true;
        }
    } else {
        if (loader->PartialCBSize == loader->CBSize) {
            cbfull = true;
        } else {
            if (loader->PartialCBSize > loader->CBSize) {
                return -4;
            }
        }
    }

    if (cbfull) {
        loader->NumPartialCB = 0;
        loader->PartialCBSize = 0;

        curcb->Flags = 0;
        curcb->Flags |= VQACBF_CBFULL | VQACBF_CBCOMP;

        loader->FullCB = curcb;
        loader->CurCB = curcb->Next;

        if (vqap->Header.Version < 3) {
            curcb->Buffer[loader->CBSize + curcb->CBOffset + 1] = 0x80;
        }
    }

    return -1;
}
