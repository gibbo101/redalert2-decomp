// int __fastcall VQA_Unknown_0077C920(VQAHandle *vqa, int *blockw, int *blockh, int *clrmode) -- 0x0077C920
// Purpose: VQA_GetBlockInfo (TS): the block width, height and color mode.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C920(VQAHandle *vqa, int *blockw, int *blockh, int *clrmode)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQAHeader *header;

    header = &vqap->Header;
    *blockw = header->BlockWidth;
    *blockh = header->BlockHeight;
    *clrmode = header->ColorMode;
    return -1;
}
