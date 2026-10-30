// long __fastcall Load_CLIP(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077A340
// Purpose: reads the CLIP chunk into ClipWidth/ClipHeight.
#include "shared/vqa_player.hpp"

long __fastcall Load_CLIP(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&vqap->ClipWidth, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}
