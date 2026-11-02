// HWND __fastcall Get_Modeless_Dialog_From_Name(char const *name) -- 0x005B60B0 (Westwood msgloop.cpp)
#include "shared/msgloop.hpp"
#include "shared/crt_string.hpp"
// @ref ?_ModelessDialogs@@3V?$DynamicVectorClass@PAUHWND__@@@@A=00a71900
// @ref _?_wname@?1??Get_Modeless_Dialog_From_Name@@YIPAUHWND__@@PBD@Z@4PADA=00a71940
// @ref __imp__GetWindowTextA@12=0079a4e8

WIN32_IMPORT int WINAPI GetWindowTextA(HWND window, char *text, int length);

HWND __fastcall Get_Modeless_Dialog_From_Name(char const *name)
{
    static char _wname[100];

    for (int i = 0; i < _ModelessDialogs.Count(); i++) {
        GetWindowTextA(_ModelessDialogs[i], _wname, sizeof(_wname) - 1);
        if (!strcmp(_wname, name)) {
            return _ModelessDialogs[i];
        }
    }
    return 0;
}
