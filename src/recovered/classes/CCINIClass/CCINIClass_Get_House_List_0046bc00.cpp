// CCINIClass::Get_House_List (0x0046BC00).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ?Find_Index@HouseTypeClass@@SIHPBD@Z=004f94d0
// @ref ?Find_Index@SideClass@@SIHPBD@Z=0067af90
// @ref ?Sides@@3V?$DynamicVectorClass@PAVSideClass@@@@A=008661b0
#include "shared/ccini_extra.hpp"

TypeList<int> CCINIClass::Get_House_List(char const *section, char const *entry, TypeList<int> defvalue)
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<int> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            int index = HouseTypeClass::Find_Index(token);
            if (index != -1) {
                list.Add(index);
            } else {
                int side = SideClass::Find_Index(token);
                if (side != -1) {
                    SideClass *sideptr = Sides[side];
                    for (int house = 0; house < sideptr->Houses.Count(); house++) {
                        list.Add(sideptr->Houses[house]);
                    }
                }
            }
        }
        return list;
    }
    return defvalue;
}
