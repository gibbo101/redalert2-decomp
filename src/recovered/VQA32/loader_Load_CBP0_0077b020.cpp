// long __fastcall Load_CBP0(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B020
// Purpose: appends an uncompressed partial codebook; completes the codebook at the group size.
#include "shared/vqa_player.hpp"

long __fastcall Load_CBP0(VQAHandleP *vqap, unsigned long iffsize)
{
    VQALoader *loader;
    VQACBNode *curcb;
    VQAHeader *header;
    unsigned char *buffer;
    int cbfull;

    loader = &vqap->Loader;
    curcb = loader->CurCB;
    header = &vqap->Header;
    if (header->Groupsize == 0 && loader->PartialCBSize == 0) {
        loader->CBSize = VQA_GetCodebookSize(vqap, loader->CurFrameNum);
    }
    buffer = curcb->Buffer + loader->PartialCBSize;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, PADSIZE(iffsize))) {
        return -4;
    }
    loader->PartialCBSize += iffsize;
    loader->NumPartialCB++;
    cbfull = false;
    if (header->Groupsize != 0) {
        if (loader->NumPartialCB == vqap->Header.Groupsize) {
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
        curcb->CodebookSize = loader->PartialCBSize;
        loader->NumPartialCB = 0;
        loader->PartialCBSize = 0;
        curcb->Flags = 0;
        curcb->CBOffset = 0;
        curcb->Flags |= 8;
        loader->FullCB = curcb;
        loader->CurCB = curcb->Next;
    }
    return -1;
}
