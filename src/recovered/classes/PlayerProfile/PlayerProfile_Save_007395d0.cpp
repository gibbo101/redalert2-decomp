// void PlayerProfile::Save_007395d0(Wstring const &name) (0x007395D0): when the profile changed
// (+0x08), writes it into wolinfo.ini's section of the lowercased nickname (the _Default_ section
// for an empty name; a named profile only when the registry options allow it): Server, Locale,
// LocaleVerified, Country, Color, Rank, Points, Wins, Losses and Disconnects, then clears the flag.
// Creates wolinfo.ini when it does not exist.
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
// @ref ?unknown_wstring_b26418@@3VWstring@@A=00b26418
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/wol_sink.hpp"
#include "shared/wol_registry_options.hpp"

extern Wstring unknown_wstring_b26418;

void PlayerProfile::Save_007395d0(Wstring const &name)
{
    WolRegistryOptions options;
    options.Read_004ff200();
    if (!unknown_08) {
        return;
    }
    Wstring section(name);
    if (name.Length() == 0) {
        section = unknown_wstring_b26418;
    } else {
        section.To_Lower();
        if (!options.unknown_004ff2c0()) {
            return;
        }
    }
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("wolinfo.ini", 1);
    }
    if (file.Is_Available()) {
        INIClass ini;
        ini.Load(file, false);
        ini.Put_String(section, "Server", Server);
        ini.Put_Int(section, "Locale", Unknown_Value_10());
        ini.Put_Bool(section, "LocaleVerified", Verified);
        ini.Put_Int(section, "Country", Country);
        ini.Put_Int(section, "Color", Color);
        ini.Put_Int(section, "Rank", Rank);
        ini.Put_Int(section, "Points", Points);
        ini.Put_Int(section, "Wins", Wins);
        ini.Put_Int(section, "Losses", Losses);
        ini.Put_Int(section, "Disconnects", Disconnects);
        ini.Save(file);
        file.Close();
        unknown_08 = false;
    }
}
