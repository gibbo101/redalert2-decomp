// void __fastcall VQA_ResetCache(VQAHandleP *vqap) -- 0x0077C880
// Purpose: empties the loop cache window (ID, Min and Max -1).
#include "shared/vqa_player.hpp"

void __fastcall VQA_ResetCache(VQAHandleP *vqap)
{
    vqap->LoopCache.ID = -1;
    vqap->LoopCache.Min = -1;
    vqap->LoopCache.Max = -1;
}
