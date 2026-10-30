// int __fastcall VQA_Unknown_0077CBA0(VQAHandle *vqa) -- 0x0077CBA0
// Purpose: VQA_GetMovieTime (TS): the clock of a public handle.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077CBA0(VQAHandle *vqa)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQAConfig *config = &vqap->Config;
    unsigned long rate = config->RefreshRate;
    unsigned long ticks = (config->TimerCallback((VQAHandle *)vqap) * 60) / rate;
    ticks += vqap->TickOffset;
    return ticks;
}
