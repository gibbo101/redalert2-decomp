// CCINIClass::Get_Anim_Target_List (0x0046B460).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ?From_Name@InfantryTypeClass@@SIHPBD@Z=0050a070
// @ref ?From_Name@UnitTypeClass@@SIHPBD@Z=0070a890
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ?As_Type@TargetClass@@QBEPAVAbstractTypeClass@@XZ=006b5d20
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
#include "shared/ccini_extra.hpp"

TypeList<int> CCINIClass::Get_Anim_Target_List(char const *section, char const *entry, TypeList<int> defvalue)
{
    char buffer[512];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<int> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            TargetClass target;
            int index = InfantryTypeClass::From_Name(token);
            if (index != -1) {
                target = TargetClass(InfantryTypes[index]);
            } else {
                index = UnitTypeClass::From_Name(token);
                if (index == -1) {
                    continue;
                }
                target = TargetClass(UnitTypes[index]);
            }
            if (target.Is_Valid()) {
                list.Add(target.As_Target());
            }
        }
        return list;
    }
    return defvalue;
}
