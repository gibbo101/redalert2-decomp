// Difficulty_Get (0x0064DB60): one difficulty level's section into a DifficultyClass
// (__fastcall: the INI in ECX, the record in EDX). Called by RulesClass::Difficulty.
// @ref ??_C@_03CEPL@ROF?$AA@=007dae30
// @ref ??_C@_04IHF@Cost?$AA@=007dae28
// @ref ??_C@_05KFDN@Armor?$AA@=007d3824
// @ref ??_C@_08DELK@Airspeed?$AA@=007dae34
// @ref ??_C@_09IBAD@FirePower?$AA@=007f1b0c
// @ref ??_C@_09JFOK@BuildTime?$AA@=007dae1c
// @ref ??_C@_0L@PONL@BuildDelay?$AA@=007f1af4
// @ref ??_C@_0M@CGIC@Groundspeed?$AA@=007dae40
// @ref ??_C@_0M@EOND@RepairDelay?$AA@=007f1b00
// @ref ??_C@_0M@KHHB@ContentScan?$AA@=007f1a34
// @ref ??_C@_0N@BLEO@DestroyWalls?$AA@=007f1ad4
// @ref ??_C@_0O@FJEM@BuildSlowdown?$AA@=007f1ae4
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"

void __fastcall Difficulty_Get(CCINIClass &ini, DifficultyClass &diff, char const *section)
{
    if (ini.Is_Present(section)) {
        diff.FirePower = ini.Get_Double(section, "FirePower", 1.0);
        diff.GroundSpeed = ini.Get_Double(section, "Groundspeed", 1.0);
        diff.AirSpeed = ini.Get_Double(section, "Airspeed", 1.0);
        diff.Armor = ini.Get_Double(section, "Armor", 1.0);
        diff.ROF = ini.Get_Double(section, "ROF", 1.0);
        diff.Cost = ini.Get_Double(section, "Cost", 1.0);
        diff.RepairDelay = ini.Get_Double(section, "RepairDelay", 0.02);
        diff.BuildDelay = ini.Get_Double(section, "BuildDelay", 0.03);
        diff.BuildSlowdown = ini.Get_Bool(section, "BuildSlowdown", false);
        diff.BuildTime = ini.Get_Double(section, "BuildTime", 1.0);
        diff.DestroyWalls = ini.Get_Bool(section, "DestroyWalls", true);
        diff.ContentScan = ini.Get_Bool(section, "ContentScan", false);
    }
}
