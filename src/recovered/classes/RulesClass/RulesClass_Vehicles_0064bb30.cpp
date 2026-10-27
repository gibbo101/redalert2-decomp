// RulesClass::Vehicles (0x0064BB30)
// @ref _RulesSection_VehicleTypes=007a906c
// @ref ??_C@_0N@CMLH@VehicleTypes?$AA@=007eec6c
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a UnitTypeClass for every name listed in [VehicleTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/unit_type.hpp"

bool RulesClass::Vehicles(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_VehicleTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_VehicleTypes, ini.Get_Entry(RulesSection_VehicleTypes, index), "", buffer, sizeof(buffer))) {
            UnitTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
