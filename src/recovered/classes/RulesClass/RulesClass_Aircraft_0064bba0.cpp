// RulesClass::Aircraft (0x0064BBA0)
// @ref _RulesSection_AircraftTypes=007a9070
// @ref ??_C@_0O@POPN@AircraftTypes?$AA@=007eec5c
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a AircraftTypeClass for every name listed in [AircraftTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/aircraft_type.hpp"

bool RulesClass::Aircraft(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_AircraftTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_AircraftTypes, ini.Get_Entry(RulesSection_AircraftTypes, index), "", buffer, sizeof(buffer))) {
            AircraftTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
