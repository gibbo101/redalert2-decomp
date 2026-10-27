// rc_ptr<PlayerProfile> __fastcall PlayerProfile::Load_00738880(Wstring const &name) (0x00738880):
// the profile in wolinfo.ini's section of the lowercased nickname (Server, Locale, LocaleVerified,
// Country, Color, Rank, Points, Wins, Losses, Disconnects); Load_Default when the file or the
// section is missing. Creates wolinfo.ini when it does not exist.
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_C@_06HCAM@Server?$AA@=007fd200
// @ref ??_C@_06JMBM@Locale?$AA@=007fd1f8
// @ref ??_C@_07FNCB@Country?$AA@=007da834
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_04DPBE@Rank?$AA@=007fd230
// @ref ??_C@_06PKIA@Points?$AA@=007f78cc
// @ref ??_C@_04OCHD@Wins?$AA@=007fd228
// @ref ??_C@_06LJIG@Losses?$AA@=007fd220
// @ref ??_C@_0M@EEO@Disconnects?$AA@=007fd214
// @ref ??_C@_0P@HNKG@LocaleVerified?$AA@=007fd238
// @ref ??0PlayerProfile@@QAE@ABVWstring@@H_NHHHHHHHH@Z=00738c40
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/wol_sink.hpp"

rc_ptr<PlayerProfile> __fastcall PlayerProfile::Load_00738880(Wstring const &name)
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("wolinfo.ini", 1);
    }
    if (!file.Is_Available()) {
        return Load_Default();
    }
    INIClass ini;
    ini.Load(file, false);
    file.Close();
    Wstring section(name);
    section.To_Lower();
    if (!ini.Find_Section(section)) {
        return Load_Default();
    }
    Wstring server;
    ini.Get_String(section, "Server", server, server);
    int locale = ini.Get_Int(section, "Locale", 0);
    bool verified = ini.Get_Bool(section.Get(), "LocaleVerified", false);
    int country = ini.Get_Int(section, "Country", -2);
    int color = ini.Get_Int(section, "Color", -2);
    int rank = ini.Get_Int(section, "Rank", -1);
    int points = ini.Get_Int(section, "Points", -1);
    int wins = ini.Get_Int(section, "Wins", -1);
    int losses = ini.Get_Int(section, "Losses", -1);
    int disconnects = ini.Get_Int(section, "Disconnects", -1);
    return rc_ptr<PlayerProfile>(new PlayerProfile(server, locale, verified, verified ? 1 : 3, country, color,
                                                   rank, points, wins, losses, disconnects));
}
