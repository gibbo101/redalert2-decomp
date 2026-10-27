// bool AITriggerTypeClass::Read_INI(CCINIClass &ini) (0x0041D7E0, slot 25)
// Parses this type's comma-separated line under [AITriggerTypes] in the
// order Write_INI writes it: name, team 1, house ("<all>", "<none>" or a
// house type), an ignored field, condition type, the object type
// (infantry, unit, aircraft or building), the comparator as hex digit
// pairs, the three weights (whole numbers), flags and team 2. Missing
// fields up to the comparator fail the read; later ones keep their value.
// unknown_b0 ends as the highest tech level of either team's task force.
#include "shared/ai_trigger_type.hpp"
// @ref ?unknown_none_name_7ceacc@@3PBDB=007ceacc
// @ref ?unknown_all_name_7cead0@@3PBDB=007cead0
// @ref ?unknown_section_79b748@@3PBDB=0079b748
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref _strtok=00782ec2
// @ref _strncpy=007823d0
// @ref __stricmp=00781f20
// @ref _atoi=00782dfd
// @ref _atof=00782f66
// @ref _strtol=00782fbd
// @ref _isspace=00782be1
// @ref __ftol=0077f110
// @ref ??_C@_02EEGL@00?$AA@=007ceb3c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?strtrim@@YIPADPAD@Z=006eef10
// @ref ?Find_By_ID_Or_Name@TeamTypeClass@@SIPAV1@PBD@Z=006bf260
// @ref ?Max_Tech_Level@TaskForceClass@@QBEHXZ=006b7140
// @ref ?Find_Index@HouseTypeClass@@SIHPBD@Z=004f94d0
// @ref ?From_Name@InfantryTypeClass@@SIHPBD@Z=0050a070
// @ref ?From_Name@UnitTypeClass@@SIHPBD@Z=0070a890
// @ref ?From_Name@AircraftTypeClass@@SIHPBD@Z=0041be60
// @ref ?BuildingType_From_Name_4583d0@@YIHPBD@Z=004583d0
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

bool AITriggerTypeClass::Read_INI(CCINIClass &ini)
{
    char buffer[0x200];
    char name[0x18];

    if (ini.Get_String(unknown_section_79b748, ID, "", buffer, sizeof(buffer))) {
        char *token = strtok(buffer, ",");
        if (token != 0) {
            FixedString<49> name49(token);
            Name = name49;
            token = strtok(0, ",");
            if (token != 0) {
                strncpy(name, token, sizeof(name));
                name[sizeof(name) - 1] = '\0';
                strtrim(name);
                unknown_dc = 0;
                if (_stricmp(name, unknown_none_name_7ceacc) != 0) {
                    unknown_dc = TeamTypeClass::Find_By_ID_Or_Name(name);
                }
                token = strtok(0, ",");
                if (token != 0) {
                    strncpy(name, token, sizeof(name));
                    name[sizeof(name) - 1] = '\0';
                    strtrim(name);
                    unknown_a0 = 0;
                    unknown_a8 = -1;
                    if (_stricmp(name, unknown_all_name_7cead0) == 0) {
                        unknown_a0 = 2;
                    } else if (_stricmp(name, unknown_none_name_7ceacc) != 0) {
                        unknown_a8 = HouseTypeClass::Find_Index(name);
                        if (unknown_a8 != -1) {
                            unknown_a0 = 1;
                        }
                    }
                    if (strtok(0, ",") != 0) {
                        unknown_b0 = 0;
                        token = strtok(0, ",");
                        if (token != 0) {
                            ConditionType = atoi(token);
                            token = strtok(0, ",");
                            if (token != 0) {
                                strncpy(name, token, sizeof(name));
                                name[sizeof(name) - 1] = '\0';
                                strtrim(name);
                                AbstractTypeClass *type = 0;
                                int index = InfantryTypeClass::From_Name(name);
                                if (index != -1) {
                                    type = (AbstractTypeClass *)InfantryTypes[index];
                                } else {
                                    index = UnitTypeClass::From_Name(name);
                                    if (index != -1) {
                                        type = (AbstractTypeClass *)UnitTypes[index];
                                    } else {
                                        index = AircraftTypeClass::From_Name(name);
                                        if (index != -1) {
                                            type = (AbstractTypeClass *)AircraftTypes[index];
                                        } else {
                                            index = BuildingType_From_Name_4583d0(name);
                                            if (index != -1) {
                                                type = (AbstractTypeClass *)BuildingTypes[index];
                                            }
                                        }
                                    }
                                }
                                unknown_d8 = type;

                                token = strtok(0, ",");
                                if (token != 0) {
                                    {
                                    char *digit = token;
                                    char digits[3] = "00";
                                    char *end = 0;
                                    unsigned count = 0;
                                    while (*digit != '\0') {
                                        while (isspace(*digit)) {
                                            digit++;
                                        }
                                        digits[0] = *digit++;
                                        if (*digit != '\0') {
                                            digits[1] = *digit++;
                                        } else {
                                            digits[1] = '\0';
                                        }
                                        if (count >= sizeof(Comparator)) break;
                                        Comparator[count++] = (unsigned char)strtol(digits, &end, 16);
                                    }
                                    }

                                    token = strtok(0, ",");
                                    if (token != 0) Weight = (unsigned)atof(token);
                                    token = strtok(0, ",");
                                    if (token != 0) MinWeight = (unsigned)atof(token);
                                    token = strtok(0, ",");
                                    if (token != 0) MaxWeight = (unsigned)atof(token);
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_d0 = atoi(token) != 0;
                                    strtok(0, ",");
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_ac = atoi(token);
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_d1 = atoi(token) != 0;

                                    token = strtok(0, ",");
                                    if (token != 0) {
                                        char team2[0x18];
                                        strncpy(team2, token, sizeof(team2));
                                        team2[sizeof(team2) - 1] = '\0';
                                        strtrim(team2);
                                        unknown_e0 = 0;
                                        if (_stricmp(team2, unknown_none_name_7ceacc) != 0) {
                                            unknown_e0 = TeamTypeClass::Find_By_ID_Or_Name(team2);
                                        }
                                    }
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_d2 = atoi(token) != 0;
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_d3 = atoi(token) != 0;
                                    token = strtok(0, ",");
                                    if (token != 0) unknown_d4 = atoi(token) != 0;

                                    if (unknown_dc != 0) {
                                        unknown_b0 = MAX(unknown_b0, unknown_dc->TaskForce->Max_Tech_Level());
                                    }
                                    if (unknown_e0 != 0) {
                                        unknown_b0 = MAX(unknown_b0, unknown_e0->TaskForce->Max_Tech_Level());
                                    }
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
