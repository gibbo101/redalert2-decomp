// void __fastcall Set_Add_Match_Buddies_00738fa0(bool value) (0x00738fa0)
// @ref ??_C@_03KFDM@Ask?$AA@=007fd264
// @ref ??_C@_0BA@MEKO@AddMatchBuddies?$AA@=007fd274
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// Writes the [Ask] AddMatchBuddies= option to wolinfo.ini (created when missing).
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

void __fastcall Set_Add_Match_Buddies_00738fa0(bool value)
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
        ini.Put_Bool("Ask", "AddMatchBuddies", value);
        ini.Save(file);
    }
}
