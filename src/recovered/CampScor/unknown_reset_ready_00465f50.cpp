// void __fastcall unknown_reset_ready(int count) -- 0x00465F50
// Marks all eight player rows ready, then the first count rows not ready.
// @ref ?unknown_score_ready_8504c8@@3PA_NA=008504c8
#include "shared/campaign_score.hpp"

void __fastcall unknown_reset_ready_465f50(int count)
{
    memset(unknown_score_ready_8504c8, true, sizeof(unknown_score_ready_8504c8));
    for (int i = 0; i < count; i++) {
        unknown_score_ready_8504c8[i] = false;
    }
}
