// bool AITriggerTypeClass::Write_INI(CCINIClass &ini) const (0x0041DD60)
// Writes this type's line under [AITriggerTypes] in the order Read_INI
// parses it: name, team 1, house ("<all>", "<none>" or the house type),
// tech level, condition type, the object type, the comparator as hex digit
// pairs, the three weights, flags (one field always 0) and team 2.
#include "shared/ai_trigger_type.hpp"
// @ref ?unknown_none_name_7ceacc@@3PBDB=007ceacc
// @ref ?unknown_all_name_7cead0@@3PBDB=007cead0
// @ref ?unknown_section_79b748@@3PBDB=0079b748
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
// @ref ?Put_String@INIClass@@QAE_NPBD00@Z=0050e5f0
// @ref _sprintf=007820f4



bool AITriggerTypeClass::Write_INI(CCINIClass &ini) const
{
    char const *team1 = unknown_none_name_7ceacc;
    char const *team2 = unknown_none_name_7ceacc;
    char const *house = unknown_none_name_7ceacc;
    char const *object = unknown_none_name_7ceacc;
    if (unknown_dc != 0) {
        team1 = unknown_dc->ID;
    }
    if (unknown_e0 != 0) {
        team2 = unknown_e0->ID;
    }
    switch (unknown_a0) {
    case 1:
        if (unknown_a8 != -1) {
            house = HouseTypes[unknown_a8]->ID;
        }
        break;
    case 2:
        house = unknown_all_name_7cead0;
        break;
    }
    if (unknown_d8 != 0) {
        object = unknown_d8->ID;
    }

    char comparator[0x200];
    char *digit;
    unsigned index;
    for (index = 0, digit = comparator; index < sizeof(Comparator); index++, digit += 2) {
        sprintf(digit, "%02x", Comparator[index]);
    }
    *digit = '\0';

    char buffer[0x200];
    sprintf(buffer, "%s,%s,%s,%d,%d,%s,%s,%lf,%lf,%lf,%d,%d,%d,%d,%s,%d,%d,%d",
            (char const *)Name, team1, house, unknown_b0, ConditionType, object, comparator,
            Weight, MinWeight, MaxWeight, unknown_d0 != 0, 0, unknown_ac, unknown_d1 != 0,
            team2, unknown_d2 != 0, unknown_d3 != 0, unknown_d4 != 0);
    return ini.Put_String(unknown_section_79b748, ID, buffer);
}
