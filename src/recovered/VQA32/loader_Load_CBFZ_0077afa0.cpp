// long __fastcall Load_CBFZ(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077AFA0
// Purpose: reads a compressed full codebook into the end of the codebook buffer.
#include "shared/vqa_player.hpp"

long __fastcall Load_CBFZ(VQAHandleP *vqap, unsigned long iffsize)
{
    VQALoader *loader;
    VQACBNode *curcb;
    unsigned char *buffer;
    unsigned long padsize;
    unsigned long lcwoffset;

    loader = &vqap->Loader;
    curcb = loader->CurCB;
    padsize = PADSIZE(iffsize);
    lcwoffset = vqap->Max_CB_Size - padsize;
    buffer = curcb->Buffer + lcwoffset;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, padsize)) {
        return -4;
    }
    loader->NumPartialCB = 0;
    curcb->Flags = 0;
    curcb->Flags |= 8 | 2;
    curcb->CBOffset = lcwoffset;
    loader->FullCB = curcb;
    loader->CurCB = curcb->Next;
    if (vqap->Header.Version < 3) {
        buffer[iffsize + 1] = 0x80;
    }
    return -1;
}
