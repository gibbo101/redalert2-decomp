// int __fastcall VQA_GetLoopCount(VQAHandleP *vqap) -- 0x0077C7C0
// Purpose: the number of loops in the LINF table.
#include "shared/vqa_player.hpp"

int __fastcall VQA_GetLoopCount(VQAHandleP *vqap)
{
    return vqap->LoopInfo.Header.Count;
}
