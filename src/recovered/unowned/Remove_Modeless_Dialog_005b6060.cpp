// void __fastcall Remove_Modeless_Dialog(HWND dialog) -- 0x005B6060 (Westwood msgloop.cpp)
#include "shared/msgloop.hpp"
#include "shared/crt_string.hpp"
// @ref ?_ModelessDialogs@@3V?$DynamicVectorClass@PAUHWND__@@@@A=00a71900

void __fastcall Remove_Modeless_Dialog(HWND dialog)
{
    _ModelessDialogs.Delete(dialog);
}
