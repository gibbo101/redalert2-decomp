// long __fastcall PageFlip_MCGABuf(VQAHandle *vqa) -- 0x007783A0
// Purpose: the buffered page flipper: reports a new palette to the event
// handler and runs the drawer callback (-2 stops); the drawer decoded it.
#include "shared/vqa_player.hpp"

long __fastcall PageFlip_MCGABuf(VQAHandle *vqa)
{
    VQAHandleP *vqap;
    VQADrawer *drawer;
    VQAFrameNode *curframe;
    VQAConfig *config;
    unsigned char *pal;
    long palsize;

    vqap = (VQAHandleP *)vqa;
    config = &vqap->Config;
    drawer = &vqap->Drawer;
    curframe = vqap->Flipper.CurFrame;

    if ((curframe->Flags & VQAFRMF_PALETTE) || (drawer->Flags & VQADRWF_SETPAL)) {
        pal = curframe->Palette;
        palsize = curframe->PaletteSize;
        if (curframe->Flags & VQAFRMF_PALETTE) {
            if (config->EventHandler != 0) {
                config->EventHandler(vqa, VQAEVENT_PALETTE, (int)pal, palsize);
            }
        } else if (drawer->Flags & VQADRWF_SETPAL) {
            drawer->Flags &= ~VQADRWF_SETPAL;
            if (config->EventHandler != 0) {
                config->EventHandler(vqa, VQAEVENT_PALETTE, (int)drawer->Palette_24, drawer->CurPalSize);
            }
        }
    }

    if (config->DrawerCallback != 0) {
        if (config->DrawerCallback(vqa, curframe->FrameNum) != 0) {
            return -2;
        }
    }
    return -1;
}
