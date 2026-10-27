// void __fastcall HouseClass::Write_Scenario_INI(CCINIClass &ini) (0x004EC180)
// The [Houses] list (index = name), then each house's own section.
#include "shared/techno.hpp"

void __fastcall HouseClass::Write_Scenario_INI(CCINIClass &ini)
{
    ini.Clear("Houses", 0);
    for (int index = 0; index < Houses.Count(); index++) {
        char name[32];
        char entry[32];
        strcpy(name, Houses[index]->IniName);
        sprintf(entry, "%d", index);
        ini.Put_String("Houses", entry, name);
    }
    for (int i = 0; i < Houses.Count(); i++) {
        Houses[i]->Write_INI(ini);
    }
}
