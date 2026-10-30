// int __fastcall VQA_GetClipping(VQAHandleP *vqap, int &clipw, long &cliph) -- 0x0077C8E0
// Purpose: the clip size from the CLIP chunk, else the image size.
#include "shared/vqa_player.hpp"

int __fastcall VQA_GetClipping(VQAHandleP *vqap, int &clipw, long &cliph)
{
    if (vqap->ClipWidth > 0) {
        clipw = vqap->ClipWidth;
        cliph = vqap->ClipHeight;
    } else {
        clipw = vqap->ImageWidth;
        cliph = vqap->ImageHeight;
    }
    return -1;
}
