// long __fastcall Load_VQF(VQAHandleP *vqap, unsigned long frame_iffsize, char flags) -- 0x00779E90
// Purpose: reads the chunks of one VQFR/VQFK frame container. The CBF0, CPL0, VPT0 and
// VPTZ readers are static helpers expanded here. VPKZ goes through its own
// copy of the VPTZ reader (Load_VPKZ): the expanded VPKZ case evaluates the
// buffer offset before the frame node, unlike the VPTZ/VPDZ/VPRZ cases
// (hypothesis that reproduces both orders).
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Load_CBFZ@@YIJPAUVQAHandleP@@K@Z=0077afa0
// @ref ?Load_CBP0@@YIJPAUVQAHandleP@@K@Z=0077b020
// @ref ?Load_CBPZ@@YIJPAUVQAHandleP@@K@Z=0077b140
// @ref ?Load_CPLZ@@YIJPAUVQAHandleP@@K@Z=0077b2c0

static long Load_CBF0(VQAHandleP *vqap, unsigned long iffsize)
{
    VQALoader *loader;
    VQACBNode *curcb;

    loader = &vqap->Loader;
    curcb = loader->CurCB;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)curcb->Buffer, PADSIZE(iffsize))) {
        return -4;
    }
    loader->NumPartialCB = 0;
    curcb->Flags = 0;
    curcb->CBOffset = 0;
    curcb->CodebookSize = iffsize;
    curcb->Flags |= 8;
    loader->FullCB = curcb;
    loader->CurCB = curcb->Next;
    return -1;
}
static long Load_CPL0(VQAHandleP *vqap, unsigned long iffsize)
{
    VQADrawer *drawer;
    VQAFrameNode *curframe;

    drawer = &vqap->Drawer;
    curframe = vqap->Loader.CurFrame;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)curframe->Palette, PADSIZE(iffsize))) {
        return -4;
    }
    curframe->Flags &= ~8;
    curframe->PalOffset = 0;
    curframe->PaletteSize = iffsize;
    if (vqap->PaletteInfo.Header.Count == 1) {
        memcpy(drawer->Palette_24, curframe->Palette, curframe->PaletteSize);
        drawer->CurPalSize = curframe->PaletteSize;
        drawer->Flags |= 1;
    }
    return -1;
}
static long Load_VPT0(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAFrameNode *curframe;

    curframe = vqap->Loader.CurFrame;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)curframe->Pointers, PADSIZE(iffsize))) {
        return -4;
    }
    curframe->Flags &= ~0x10;
    curframe->PtrOffset = 0;
    return -1;
}
static long Load_VPTZ(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAFrameNode *curframe;
    unsigned char *buffer;
    unsigned long padsize;
    unsigned long lcwoffset;

    curframe = vqap->Loader.CurFrame;
    padsize = PADSIZE(iffsize);
    lcwoffset = vqap->Max_Ptr_Size - padsize;
    buffer = curframe->Pointers + lcwoffset;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, padsize)) {
        return -4;
    }
    curframe->Flags |= 0x10;
    curframe->PtrOffset = lcwoffset;
    if (vqap->Header.Version < 3) {
        buffer[iffsize + 1] = 0x80;
    }
    return -1;
}
static long Load_VPKZ(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAFrameNode *curframe;
    unsigned char *buffer;
    unsigned long padsize;
    unsigned long lcwoffset;

    padsize = PADSIZE(iffsize);
    lcwoffset = vqap->Max_Ptr_Size - padsize;
    curframe = vqap->Loader.CurFrame;
    buffer = curframe->Pointers + lcwoffset;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, padsize)) {
        return -4;
    }
    curframe->Flags |= 0x10;
    curframe->PtrOffset = lcwoffset;
    if (vqap->Header.Version < 3) {
        buffer[iffsize + 1] = 0x80;
    }
    return -1;
}

long __fastcall Load_VQF(VQAHandleP *vqap, unsigned long frame_iffsize, char flags)
{
    VQAFrameNode *curframe;
    VQAChunkHeader *chunk;
    unsigned long iffsize;
    unsigned long framesize;
    unsigned long bytes_loaded = 0;
    VQADrawer *drawer;
    VQAConfig *config;
    int skip;

    curframe = vqap->Loader.CurFrame;
    drawer = &(vqap->Drawer);
    chunk = &vqap->Loader.CurChunkHdr;
    config = &(vqap->Config);
    framesize = PADSIZE(frame_iffsize);

    while (bytes_loaded < framesize) {
        if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)chunk, sizeof(*chunk))) {
            return -2;
        }
        iffsize = REVERSE_LONG(chunk->Size);
        bytes_loaded += sizeof(*chunk);
        bytes_loaded += PADSIZE(iffsize);
        skip = true;
        switch (chunk->ID) {
        case ID_CBF0:
            if (flags & 0x10) {
                break;
            }
            if (Load_CBF0(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_CBFZ:
            if (flags & 0x10) {
                break;
            }
            if (Load_CBFZ(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_CBP0:
            if (flags & 8) {
                break;
            }
            if (Load_CBP0(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_CBPZ:
            if (flags & 8) {
                break;
            }
            if (Load_CBPZ(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_CPL0:
            if (flags & 1) {
                break;
            }
            if (Load_CPL0(vqap, iffsize) != -1) {
                return -4;
            }
            curframe->Flags |= 4;
            skip = false;
            break;
        case ID_CPLZ:
            if (flags & 1) {
                break;
            }
            if (Load_CPLZ(vqap, iffsize) != -1) {
                return -4;
            }
            curframe->Flags |= 4;
            skip = false;
            break;
        case ID_VPT0:
        case ID_VPTD:
            if (flags & 4) {
                break;
            }
            if (Load_VPT0(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_VPTZ:
        case ID_VPDZ:
            if (flags & 4) {
                break;
            }
            if (Load_VPTZ(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            break;
        case ID_VPTK:
            if (flags & 4) {
                break;
            }
            if (Load_VPT0(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            curframe->Flags |= 2;
            break;
        case ID_VPTR:
            if (flags & 4) {
                break;
            }
            if (Load_VPT0(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            curframe->Flags |= 0x20;
            break;
        case ID_VPKZ:
            if (flags & 4) {
                break;
            }
            if (Load_VPKZ(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            curframe->Flags |= 2;
            break;
        case ID_VPRZ:
            if (flags & 4) {
                break;
            }
            if (Load_VPTZ(vqap, iffsize) != -1) {
                return -4;
            }
            skip = false;
            curframe->Flags |= 0x20;
            break;
        default:
            return -4;
        }
        if (skip == true) {
            if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 1, PADSIZE(iffsize))) {
                return -6;
            }
        }
    }
    return -1;
}
