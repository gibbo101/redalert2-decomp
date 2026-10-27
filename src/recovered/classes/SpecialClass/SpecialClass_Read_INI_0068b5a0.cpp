// void SpecialClass::Read_INI(INIClass &ini) (0x0068B5A0, name hypothesis)
// Reads the options from [SpecialFlags]; the Tiberium, bridge, alliance, fog,
// inert and harvester options are only read outside multiplayer-style games
// (0x00A3D298 is zero) or when 0x00A40D13 is set.
#include "shared/special.hpp"
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ?unknown_special_section_7f43f4@@3PADA=007f43f4
// @ref ??_C@_05LCNE@Inert?$AA@=007f445c
// @ref ??_C@_08HEJL@FogOfWar?$AA@=007f1508
// @ref ??_C@_09FJIK@IonStorms?$AA@=007f4450
// @ref ??_C@_09JPID@MCVDeploy?$AA@=007f4494
// @ref ??_C@_0BA@DBGD@TiberiumSpreads?$AA@=007f44b4
// @ref ??_C@_0BA@JPFK@HarvesterImmune?$AA@=007f4464
// @ref ??_C@_0BC@HFBP@TiberiumExplosive?$AA@=007efae4
// @ref ??_C@_0BD@LDJE@DestroyableBridges?$AA@=007f44a0
// @ref ??_C@_0L@HKMP@Meteorites?$AA@=007f4444
// @ref ??_C@_0L@IIPO@Visceroids?$AA@=007f4438
// @ref ??_C@_0O@CCKF@TiberiumGrows?$AA@=007f158c
// @ref ??_C@_0O@LPPE@FixedAlliance?$AA@=007f4474
// @ref ??_C@_0P@BEDI@InitialVeteran?$AA@=007f4484
// @ref ?unknown_a3d298@@3HA=00a3d298
// @ref ?unknown_a40d13@@3_NA=00a40d13

extern int unknown_a3d298;      // 0x00A3D298
extern bool unknown_a40d13;     // 0x00A40D13

// The original keeps this pointer (to "SpecialFlags") as function-local static data.
extern char *unknown_special_section_7f43f4;    // 0x007f43f4

void SpecialClass::Read_INI(INIClass &ini)
{
    TiberiumExplosive = ini.Get_Bool(unknown_special_section_7f43f4, "TiberiumExplosive", TiberiumExplosive);
    MCVDeploy = ini.Get_Bool(unknown_special_section_7f43f4, "MCVDeploy", MCVDeploy);
    InitialVeteran = ini.Get_Bool(unknown_special_section_7f43f4, "InitialVeteran", InitialVeteran);
    IonStorms = ini.Get_Bool(unknown_special_section_7f43f4, "IonStorms", IonStorms);
    Meteorites = ini.Get_Bool(unknown_special_section_7f43f4, "Meteorites", Meteorites);
    Visceroids = ini.Get_Bool(unknown_special_section_7f43f4, "Visceroids", Visceroids);
    if (unknown_a3d298 == 0 || unknown_a40d13) {
        TiberiumGrows = ini.Get_Bool(unknown_special_section_7f43f4, "TiberiumGrows", TiberiumGrows);
        TiberiumSpreads = ini.Get_Bool(unknown_special_section_7f43f4, "TiberiumSpreads", TiberiumSpreads);
        DestroyableBridges = ini.Get_Bool(unknown_special_section_7f43f4, "DestroyableBridges", DestroyableBridges);
        FixedAlliance = ini.Get_Bool(unknown_special_section_7f43f4, "FixedAlliance", FixedAlliance);
        FogOfWar = ini.Get_Bool(unknown_special_section_7f43f4, "FogOfWar", FogOfWar);
        Inert = ini.Get_Bool(unknown_special_section_7f43f4, "Inert", Inert);
        HarvesterImmune = ini.Get_Bool(unknown_special_section_7f43f4, "HarvesterImmune", HarvesterImmune);
    }
}
