// void Selection::Load_Layout(INIClass &ini, Wstring const &section) (0x0072DEA0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Load_Layout(INIClass &ini, Wstring const &section)
{
    Wstring value;
    Wstring faction(Faction_Name(TheCampaign->Player_Faction()));
    if (ini.Get_String(section, faction + "ZoomingTarget", (char const *)0, value) > 0) {
        ZoomingTarget = new MSAnimEntry(value);
    }
    ini.Get_String(section, faction + "TargetPalette", (char const *)0, value);
    TargetPalette = unknown_load_drawer_5ac560(value);
    ini.Get_String(section, faction + "Target", (char const *)0, value);
    Target = new MSAnimEntry(value);
    TargetDividingFrame = ini.Get_Int(section, faction + "TargetDividingFrame", 0x20);
}
}
// @ref ??_C@_06JGPH@Target?$AA@=007f34f4
// @ref ??_C@_0BE@KBGF@TargetDividingFrame?$AA@=007fc3fc
// @ref ??_C@_0O@OENI@ZoomingTarget?$AA@=007fc420
// @ref ??_C@_0O@OHGF@TargetPalette?$AA@=007fc410
