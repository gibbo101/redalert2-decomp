// unsigned long __fastcall VQA_GetTime(VQAHandleP *vqap) -- 0x0077CB70
#include "shared/vqa_player.hpp"

unsigned long __fastcall VQA_GetTime(VQAHandleP *vqap)
{
    unsigned long ticks = (vqap->Config.TimerCallback((VQAHandle *)vqap) * 60) / vqap->Config.RefreshRate;
    ticks += vqap->TickOffset;
    return ticks;
}
