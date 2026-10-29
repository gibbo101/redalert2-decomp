// bool unknown_all_ready() -- 0x00465F80 (29 bytes; the inventory row 0x00465F96 is a false entry
// from a number table at 0x008217B0)
// Whether every player row is ready.
// @ref ?unknown_score_ready_8504c8@@3PA_NA=008504c8
#include "shared/campaign_score.hpp"

bool unknown_all_ready_465f80()
{
    int i;
    for (i = 0; i < 8; i++) {
        if (!unknown_score_ready_8504c8[i]) {
            break;
        }
    }
    return i == 8;
}
