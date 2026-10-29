// void BaseClass::Read_INI(CCINIClass &ini, char const *section) (0x0042C460)
// PercentBuilt and NodeCount, then each node "%03d" = type,x,y; the type is a
// BuildingTypes name, or a number when it starts with '-' (TS BASE.CPP Read_INI).
// The node's other two fields are left unset (BaseNodeClass(type, cell)).
#include "shared/base.hpp"
#include "shared/ccini_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/crt_tokens.hpp"
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0

void BaseClass::Read_INI(CCINIClass &ini, char const *section)
{
    PercentBuilt = ini.Get_Int(section, "PercentBuilt", PercentBuilt);
    int count = ini.Get_Int(section, "NodeCount", 0);
    for (int index = 0; index < count; index++) {
        char key[10];
        char buffer[128];
        sprintf(key, "%03d", index);
        ini.Get_String(section, key, 0, buffer, sizeof(buffer));
        int type;
        if (buffer[0] == '-') {
            type = atoi(strtok(buffer, ","));
        } else {
            type = BuildingTypeClass::From_Name(strtok(buffer, ","));
        }
        Cell cell;
        cell.X = (short)atoi(strtok(0, ","));
        cell.Y = (short)atoi(strtok(0, ","));
        Nodes.Add(BaseNodeClass(type, cell));
    }
}
