// 0x0051FC30: whether a storm is active or armed (deferment pending).
#include "shared/lightning_storm.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormDeferment@@3HA=00a51938

int __fastcall Is_Storm_Pending_0051FC30()
{
    if (StormActive || StormDeferment > 0) {
        return 1;
    }
    return 0;
}
