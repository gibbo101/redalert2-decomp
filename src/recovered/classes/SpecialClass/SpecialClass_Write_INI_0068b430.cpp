// void SpecialClass::Write_INI(INIClass &ini) const (0x0068B430, name hypothesis)
// Writes the thirteen named options to [SpecialFlags].
#include "shared/special.hpp"
// @ref ?Put_Bool@INIClass@@QAE_NPBD0_N@Z=0050f380
// @ref ?unknown_special_section_7f43f0@@3PADA=007f43f0
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

// The original keeps this pointer (to "SpecialFlags") as function-local static data.
extern char *unknown_special_section_7f43f0;    // 0x007f43f0

void SpecialClass::Write_INI(INIClass &ini) const
{
    ini.Put_Bool(unknown_special_section_7f43f0, "TiberiumGrows", TiberiumGrows);
    ini.Put_Bool(unknown_special_section_7f43f0, "TiberiumSpreads", TiberiumSpreads);
    ini.Put_Bool(unknown_special_section_7f43f0, "TiberiumExplosive", TiberiumExplosive);
    ini.Put_Bool(unknown_special_section_7f43f0, "DestroyableBridges", DestroyableBridges);
    ini.Put_Bool(unknown_special_section_7f43f0, "MCVDeploy", MCVDeploy);
    ini.Put_Bool(unknown_special_section_7f43f0, "InitialVeteran", InitialVeteran);
    ini.Put_Bool(unknown_special_section_7f43f0, "FixedAlliance", FixedAlliance);
    ini.Put_Bool(unknown_special_section_7f43f0, "HarvesterImmune", HarvesterImmune);
    ini.Put_Bool(unknown_special_section_7f43f0, "FogOfWar", FogOfWar);
    ini.Put_Bool(unknown_special_section_7f43f0, "Inert", Inert);
    ini.Put_Bool(unknown_special_section_7f43f0, "IonStorms", IonStorms);
    ini.Put_Bool(unknown_special_section_7f43f0, "Meteorites", Meteorites);
    ini.Put_Bool(unknown_special_section_7f43f0, "Visceroids", Visceroids);
}
