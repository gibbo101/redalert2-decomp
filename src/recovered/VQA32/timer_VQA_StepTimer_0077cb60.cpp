// void __fastcall VQA_StepTimer(VQAHandleP *vqap, long step) -- 0x0077CB60
#include "shared/vqa_player.hpp"

void __fastcall VQA_StepTimer(VQAHandleP *vqap, long step)
{
    vqap->TickOffset += step;
}
