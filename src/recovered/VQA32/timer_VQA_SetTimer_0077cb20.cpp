// void __fastcall VQA_SetTimer(VQAHandleP *vqap, long time) -- 0x0077CB20
// Purpose: sets the movie clock (60 ticks per second from the timer callback
// and refresh rate, offset by TickOffset) so that it reads `time` now.
#include "shared/vqa_player.hpp"

void __fastcall VQA_SetTimer(VQAHandleP *vqap, long time)
{
    vqap->TickOffset = 0;
    unsigned long curtime = VQA_GetTime(vqap);
    vqap->TickOffset = time - curtime;
}
