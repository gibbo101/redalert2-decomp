// long __fastcall Load_CPLZ(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B2C0
// Purpose: reads a compressed palette; a single-palette movie unpacks it at once.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"
// @ref _VQA_LCW_Uncompress=007813eb

long __fastcall Load_CPLZ(VQAHandleP *vqap, unsigned long iffsize)
{
    VQADrawer *drawer;
    VQAFrameNode *curframe;
    unsigned char *buffer;
    unsigned long padsize;
    unsigned long lcwoffset;

    curframe = vqap->Loader.CurFrame;
    padsize = PADSIZE(iffsize);
    drawer = &vqap->Drawer;
    lcwoffset = vqap->Max_Pal_Size - padsize;
    buffer = curframe->Palette + lcwoffset;
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)buffer, padsize)) {
        return -4;
    }
    curframe->Flags |= 8;
    curframe->PalOffset = lcwoffset;
    curframe->PaletteSize = iffsize;
    if (vqap->Header.Version < 3) {
        buffer[iffsize + 1] = 0x80;
    }
    if (vqap->PaletteInfo.Header.Count == 1) {
        curframe->PaletteSize = VQA_LCW_Uncompress((char *)(curframe->Palette + curframe->PalOffset), (char *)curframe->Palette, vqap->Max_Pal_Size);
        curframe->Flags &= ~8;
        memcpy(drawer->Palette_24, curframe->Palette, curframe->PaletteSize);
        drawer->CurPalSize = curframe->PaletteSize;
        drawer->Flags |= 1;
    }
    return -1;
}
