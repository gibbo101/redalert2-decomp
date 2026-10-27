// void HouseClass::Write_INI(CCINIClass &ini) (0x004EC230)
// Writes the house's own section (cleared first): Country, TechLevel,
// Credits, IQ, Edge, PlayerControl, Color, Allies (from +0x120), UIName when
// set, and the base plan.
// @ref ??_C@_02KPHM@IQ?$AA@=007da854
// @ref ??_C@_04ICPD@Edge?$AA@=007da84c
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
// @ref ??_C@_06KHDF@Allies?$AA@=007da844
// @ref ??_C@_07FNCB@Country?$AA@=007da834
// @ref ??_C@_07NGJJ@Credits?$AA@=007da8b4
// @ref ??_C@_09FKED@TechLevel?$AA@=007da8bc
// @ref ??_C@_0O@BOLA@PlayerControl?$AA@=007da8a4
// @ref ?Write_INI@BaseClass@@QAEXAAVCCINIClass@@PBD@Z=0042c5d0
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

void HouseClass::Write_INI(CCINIClass &ini)
{
    char section[20];
    strcpy(section, IniName);

    ini.Clear(section);
    ini.Put_String(section, "Country", Type->ID);
    ini.Put_Int(section, "TechLevel", unknown_11c);
    ini.Put_Int(section, "Credits", unknown_124 / 100);
    ini.Put_Int(section, "IQ", unknown_118);
    ini.Put_SourceType(section, "Edge", (SourceType)unknown_128);
    ini.Put_Bool(section, "PlayerControl", unknown_135);
    ini.Put_ColorScheme(section, "Color", ColorSchemeIndex);

    int allies = 0;
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        if (unknown_120 & (1 << house->ArrayIndex)) {
            allies |= 1 << house->ArrayIndex;
        }
    }
    ini.Put_Houses(section, "Allies", allies);

    if (unknown_15ef5[0] != 0) {
        ini.Put_String(section, "UIName", unknown_15ef5);
    }
    unknown_55f0.Write_INI(ini, section);
}
