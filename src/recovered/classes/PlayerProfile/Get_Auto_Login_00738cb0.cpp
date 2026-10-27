// bool __fastcall Get_Auto_Login_00738cb0() (0x00738cb0)
// @ref ??_C@_03KFDM@Ask?$AA@=007fd264
// @ref ??_C@_09FGAK@AutoLogin?$AA@=007fd268
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// The [Ask] AutoLogin= option of wolinfo.ini (true when absent); false without the file.
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

bool __fastcall Get_Auto_Login_00738cb0()
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        return false;
    }
    INIClass ini;
    ini.Load(file, false);
    file.Close();
    return ini.Get_Bool("Ask", "AutoLogin", true);
}
