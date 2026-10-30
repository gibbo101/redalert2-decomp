// long __fastcall Load_FINF(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077AF50
// Purpose: reads the frame offset table, or skips it without a table.
#include "shared/vqa_player.hpp"

long __fastcall Load_FINF(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Foff != 0) {
        if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)vqap->Foff, PADSIZE(iffsize))) {
            return -4;
        }
    } else {
        if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 1, PADSIZE(iffsize))) {
            return -6;
        }
    }
    return -1;
}
