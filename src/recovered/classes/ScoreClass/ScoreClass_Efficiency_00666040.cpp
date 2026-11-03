// Evaluate surviving assets and unspent income for the score screen, 0x00666040.
#include "shared/score.hpp"
#include "shared/house.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __ftol=0077f110
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@4005c800000000000000=0079b7f0

// @ref ??_C@_0BB@EIGE@Efficiency?3?5?$CFld?6?$AA@=007f2928
// @ref ??_C@_0BD@CIIH@MoneyEconomy?5?$DN?5?$CFf?6?$AA@=007f293c
// @ref ??_C@_0CK@CEDH@Money?3?5?$CFld?0?5Harvested?3?5?$CFld?0?5Init@=007f2950
// @ref ??_C@_0BD@PBNN@BuildEconomy?5?$DN?5?$CFf?6?$AA@=007f297c
// @ref ??_C@_0BM@KJJA@Remaining?3?5?$CFld?0?5Total?3?5?$CFld?6?$AA@=007f2990

int ScoreClass::Efficiency(HouseClass *house)
{
    int remain = 0;
    int total = 0;
    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *other = Houses[i];
        if ((house->Is_Ally(other) && other->Is_Ally(house)) || house == other) {
            remain += other->unknown_5460.Sum();
            remain += other->unknown_5470.Sum();
            remain += other->unknown_5480.Sum();
            remain += other->unknown_5490.Sum();
            total += other->unknown_53b4;
            total += other->unknown_5360;
        }
    }
    total += remain;
    Debug_Printf("Remaining: %ld, Total: %ld\n", remain, total);
    float build = total > 0 ? (float)remain / total : 0.0f;
    Debug_Printf("BuildEconomy = %f\n", build);
    int const &harvested = house->unknown_220;
    Debug_Printf("Money: %ld, Harvested: %ld, Initial: %ld\n", house->Available_Money(), harvested, house->unknown_124);
    total = harvested + house->unknown_124;
    float money = total > 0 ? (float)house->Available_Money() / (float)total : 0.0f;
    Debug_Printf("MoneyEconomy = %f\n", money);
    int efficiency = (int)(100.0 * ((build + money) * 0.5));
    Debug_Printf("Efficiency: %ld\n", efficiency);
    return efficiency;
}
