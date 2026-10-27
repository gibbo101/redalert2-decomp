// bool DisplayClass::unknown_slot41(int arg1, int *arg2, bool arg3) (0x00499B60, slot 41)
// Passes a request on to the tactical view: with a value or arg3 set it
// calls 0x006A8B70 (true); otherwise answers whether 0x006AA840 finds one.
#include "shared/display.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006AA840@Tactical@@QAEHH@Z=006aa840
// @ref ?Unknown_006A8B70@Tactical@@QAEXHH@Z=006a8b70

bool DisplayClass::unknown_slot41(int arg1, int *arg2, bool arg3)
{
    int value = *arg2;
    if (value == 0 && !arg3) {
        return false;
    }
    if (value != 0 && !arg3) {
        return unknown_tactical_83996c->Unknown_006AA840(arg1) != -1;
    }
    unknown_tactical_83996c->Unknown_006A8B70(arg1, value);
    return true;
}
