// rc_ptr<PlayerProfile> __fastcall PlayerProfile::Load_Default() (0x00738670): the profile in
// wolinfo.ini's [_Default_] section (unknown_wstring_b26418): Server, Locale, Country and Color
// (-2 when absent); creates wolinfo.ini when it does not exist. Name is a hypothesis.
// The section test goes through an inline Find_Section(Wstring const &) (ini_class.hpp): the
// original spends one more inline site here (its GenericList constructor stays out of line).
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
// @ref ??0PlayerProfile@@QAE@ABVWstring@@H_NHHHHHHHH@Z=00738c40
// @ref ??_C@_06HCAM@Server?$AA@=007fd200
// @ref ??_C@_06JMBM@Locale?$AA@=007fd1f8
// @ref ??_C@_07FNCB@Country?$AA@=007da834
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_G?$rc_ptr@VPlayerProfile@@@@UAEPAXI@Z=0073a0c0
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/wol_sink.hpp"

extern Wstring unknown_wstring_b26418;

rc_ptr<PlayerProfile> __fastcall PlayerProfile::Load_Default()
{
    Wstring server;
    int locale = 0;
    int country = -2;
    int color = -2;
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("wolinfo.ini", 1);
    }
    if (file.Is_Available()) {
        INIClass ini;
        ini.Load(file, false);
        file.Close();
        if (ini.Find_Section(unknown_wstring_b26418)) {
            ini.Get_String(unknown_wstring_b26418, "Server", server, server);
            locale = ini.Get_Int(unknown_wstring_b26418, "Locale", 0);
            country = ini.Get_Int(unknown_wstring_b26418, "Country", -2);
            color = ini.Get_Int(unknown_wstring_b26418, "Color", -2);
        }
    }
    return rc_ptr<PlayerProfile>(new PlayerProfile(server, locale, false, 0, country, color, -1, -1, -1, -1, -1));
}
