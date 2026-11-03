// BuildingClass::Read_INI 0x0044AB80: the [Structures] entries (TibSun building.cpp Read_INI).
// Turn_On 0x44D3E0, Power_On 0x44D600 and Adjust_House_Power 0x44FA40 are inlined; the online call goes through a
// pointer copy, which gives the original's base/index order in the inlined Power_On anim loop.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/ccini_class.hpp"
#include "shared/building_light.hpp"
#include "shared/building_type_list.hpp"
extern "C" char const *unknown_structure_section_0079cb88;
// @ref _unknown_structure_section_0079cb88=0079cb88
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd
// @ref ?Find_Index@HouseClass@@SIHPBD@Z=004f5b40
// @ref ?From_Name@BuildingTypeClass@@SIHPBD@Z=004583d0
// @ref ?From_Name@TagTypeClass@@SIPAV1@PBD@Z=006b4880
// @ref ?Find_Or_Make@TagClass@@SIPAV1@PAVTagTypeClass@@@Z=006b3d30
// @ref ?Set_Behavior@BuildingLightClass@@QAEXH@Z=00434370
// @ref __real@8@3ff78000000000000000=0079a730
extern int unknown_ini_format_a40d24;
void __fastcall BuildingClass::Read_INI(CCINIClass &ini)
{
    BuildingClass *b;
    HouseClass *bhptr;
    int classid;
    Cell cell;
    char buf[128];
    char *trigname;

    int i;
    int upgrades[3];

    for (i = 0; i < 3; i++) {
        upgrades[i] = -1;
    }

    int len = ini.Entry_Count(unknown_structure_section_0079cb88);
    for (int index = 0; index < len; index++) {
        char const *entry = ini.Get_Entry(unknown_structure_section_0079cb88, index);

        ini.Get_String(unknown_structure_section_0079cb88, entry, 0, buf, sizeof(buf));

        int bhouse = HouseClass::Find_Index(strtok(buf, ","));
        if (bhouse == -1) {
            continue;
        }
        bhptr = Houses[bhouse];

        if (bhptr == 0) {
            continue;
        }

        if (unknown_game_mode_a3d298 != 0 && bhptr == unknown_player_a35db4) {
            continue;
        }

        classid = BuildingTypeClass::From_Name(strtok(0, ","));

        if (classid != -1) {
            int strength;
            int facing;

            strength = atoi(strtok(0, ","));

            if (unknown_ini_format_a40d24 >= 4) {
                Cell parsed;
                parsed.X = (short)atoi(strtok(0, ","));
                parsed.Y = (short)atoi(strtok(0, ","));
                cell = parsed;
            } else {
                int packed = atoi(strtok(0, ","));
                cell = Cell((short)(packed % 128), (short)(packed / 128));
            }

            facing = atoi(strtok(0, ","));

            trigname = strtok(0, ",");

            bool sellable = false;
            char *token_pointer = strtok(0, ",");
            if (token_pointer) {
                sellable = atoi(token_pointer) != 0;
            }

            bool rebuild = false;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                rebuild = atoi(token_pointer) != 0;
            }

            bool online = true;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                online = atoi(token_pointer) != 0;
            }

            int upgradecount = 0;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                upgradecount = atoi(token_pointer);
            }

            int spotlight = 1;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                spotlight = atoi(token_pointer);
            }

            for (i = 0; i < 3; i++) {
                token_pointer = strtok(0, ",");
                if (token_pointer) {
                    upgrades[i] = BuildingTypeClass::From_Name(token_pointer);
                }
            }

            bool repair = false;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                repair = atoi(token_pointer) != 0;
            }

            bool nominal = false;
            token_pointer = strtok(0, ",");
            if (token_pointer) {
                nominal = atoi(token_pointer) != 0;
            }

            b = new BuildingClass(BuildingTypes[classid], bhptr);
            if (b) {

                TagTypeClass *tp = TagTypeClass::From_Name(trigname);
                if (tp) {
                    TagClass *tt = TagClass::Find_Or_Make(tp);
                    if (tt) {
                        b->Attach_Tag(tt);
                    }
                }
                b->unknown_5ac = sellable;
                b->unknown_59a = rebuild;
                b->unknown_59b = repair;
                b->unknown_599 = nominal;

                strength = (strength < 256) ? strength : 256;
                strength = b->Type->MaxStrength * (strength / 256.0);
                b->Strength = strength;
                if (b->Strength > b->Type->MaxStrength - 3) b->Strength = b->Type->MaxStrength;
                b->unknown_70 = b->Strength;

                if (b->unknown_slot53(&CoordStruct(cell), facing)) {

                    if (b->unknown_4d4) {
                        static_cast<BuildingLightClass *>(b->unknown_4d4)->Set_Behavior(spotlight);
                    }

                    if (online) {
                        if (!b->unknown_530 && b->unknown_3fc == 0) {
                            BuildingClass *building = b;
                            building->unknown_44d3e0();
                        }
                    } else {
                        b->unknown_44d530();
                    }

                    b->unknown_375 = false;

                    if (b->Type->NeedsEngineer && !b->unknown_59c) {
                        b->unknown_44d6c0();
                    }

                    if (upgradecount) {
                        for (i = 0; i < upgradecount; i++) {
                            if (upgrades[i] != -1) {
                                BuildingTypeClass *utype = BuildingTypes[upgrades[i]];
                                BuildingClass *u = new BuildingClass(utype, bhptr);
                                u->unknown_slot53(&CoordStruct(cell), facing);
                            }
                        }
                    }
                    if (b->unknown_slot232()) {
                        Building_Update_Turret_Animation_Frame_0043bce0(b);
                    }
                } else {
                    delete b;
                }
            }
        }
    }
}
