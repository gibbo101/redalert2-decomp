// 0x0051F920: sets StormActive (hypothesis: used by a load or a trigger).
#include "shared/lightning_storm.hpp"
// @ref ?StormActive@@3_NA=00a51934

void __fastcall Set_Storm_Active_0051F920(bool active)
{
    StormActive = active;
}
