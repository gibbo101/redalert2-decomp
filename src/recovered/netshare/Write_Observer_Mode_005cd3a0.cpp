// void __fastcall Unknown_005CD3A0() (0x005CD3A0)
// Writes the observer mode switch to [MultiPlayer] of RA2.INI and saves the INI file.
#include "shared/raw_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/wol_settings.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??_C@_0N@IHEM@ObserverMode?$AA@=007e740c
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8

void __fastcall Unknown_005CD3A0()
{
    RawFileClass file("RA2.INI");
    unknown_ini_839740.Put_Int("MultiPlayer", "ObserverMode", unknown_a72c68);
    unknown_ini_839740.Save(file, false);
}
