// int __fastcall VQA_GetXYPos(VQAHandleP *vqap, int &x, long &y) -- 0x0077CA50
// Purpose: the movie's position from its header.
#include "shared/vqa_player.hpp"

int __fastcall VQA_GetXYPos(VQAHandleP *vqap, int &x, long &y)
{
    VQAHeader *header;

    header = &vqap->Header;
    x = header->Xpos;
    y = header->Ypos;
    return -1;
}
