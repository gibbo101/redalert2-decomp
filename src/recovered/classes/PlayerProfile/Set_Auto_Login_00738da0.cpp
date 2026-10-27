// void __fastcall Set_Auto_Login_00738da0(bool value) (0x00738da0)
// @ref ??_C@_03KFDM@Ask?$AA@=007fd264
// @ref ??_C@_09FGAK@AutoLogin?$AA@=007fd268
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// Writes the [Ask] AutoLogin= option to wolinfo.ini (created when missing).
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

void __fastcall Set_Auto_Login_00738da0(bool value)
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("wolinfo.ini", 1);
    }
    INIClass ini;
    if (file.Is_Available()) {
        ini.Load(file, false);
        ini.Put_Bool("Ask", "AutoLogin", value);
        ini.Save(file);
    }
}
