// void __fastcall unknown_set_ready(int index, bool ready) -- 0x00465FA0 (7 bytes)
// @ref ?unknown_score_ready_8504c8@@3PA_NA=008504c8
#include "shared/campaign_score.hpp"

void __fastcall unknown_set_ready_465fa0(int index, bool ready)
{
    unknown_score_ready_8504c8[index] = ready;
}
