// Original 0x00706AE0: 1147 body bytes and 5 independently bounded NOP bytes.
// Creates scenario units from [Units], then resolves their linked-unit indices.
#include "shared/unit.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cell.hpp"
#include "shared/techno_map.hpp"
#include "shared/tag.hpp"
#include "shared/unknown_geometry.hpp"
extern char const *unknown_units_section_7addc0;
extern int unknown_ini_format_a40d24;
extern int unknown_bridge_height_ad057c;
// @ref ?unknown_bridge_height_ad057c@@3HA=00ad057c
// @ref ?unknown_units_section_7addc0@@3PBDB=007addc0
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd
// @ref ?Find_Index@HouseClass@@SIHPBD@Z=004f5b40
// @ref ?From_Name@UnitTypeClass@@SIHPBD@Z=0070a890
// @ref ?Mission_From_Name@MissionClass@@SIHPBD@Z=00594fe0
// @ref ?From_Name@TagTypeClass@@SIPAV1@PBD@Z=006b4880
// @ref ?Find_Or_Make@TagClass@@SIPAV1@PAVTagTypeClass@@@Z=006b3d30
// @ref ?Attach_Tag@ObjectClass@@QAE_NPAVTagClass@@@Z=005d4430
// @ref ?Unknown_00713590@UnknownTechnoPair@@QAEXH@Z=00713590
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// VC6 health block emits exact original native instructions, without a float32 store. This does not establish a portable source-width contract.
static inline UnitTypeClass *Unit_Read_Float_Health_00706AE0(UnitClass &unit, float health)
{
    UnitTypeClass *type = unit.Type;
    unit.Strength = (int)((double)health * type->MaxStrength * (1.0 / 256.0));
    return type;
}
static inline void Resolve_Unit_Link(int link_index,unsigned linked_link_index)
{
    UnitClass *unit = Units[link_index];
    if (linked_link_index == (unsigned)-1 || linked_link_index >= (unsigned)Units.Count()) {
        unit->unknown_5b0 = 0;
    } else {
        UnitClass *linked = Units[linked_link_index];
        unit->unknown_5b0 = linked;
        linked->unknown_5b8 = true;
    }
}
void __fastcall UnitClass::Read_INI(CCINIClass &ini)
{
    DynamicVectorClass<int> links;
    links.Clear();
    int count = ini.Entry_Count(unknown_units_section_7addc0);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_units_section_7addc0, index);
        char buffer[128];
        ini.Get_String(unknown_units_section_7addc0, entry, 0, buffer, sizeof(buffer));
        int house_index = HouseClass::Find_Index(strtok(buffer, ","));
        if (house_index != -1) {
            int type_index = UnitTypeClass::From_Name(strtok(0, ","));
            HouseClass *house = Houses[house_index];
            if (type_index != -1) {
                UnitClass *unit = new UnitClass(UnitTypes[type_index], house);
                if (unit != 0) {
                    int health = atoi(strtok(0, ","));
                    Cell cell;
                    if (unknown_ini_format_a40d24 >= 4) {
                        int x = atoi(strtok(0, ","));
                        short y = (short)atoi(strtok(0, ","));
                        cell = Cell((short)x, y);
                    } else {
                        int packed = atoi(strtok(0, ","));
                        cell = Cell((short)(packed % 128), (short)(packed / 128));
                    }
                    CoordStruct coord = Cell_Center(cell);
                    int direction = atoi(strtok(0, ","));
                    int mission = MissionClass::Mission_From_Name(strtok(0, ","));
                    TagTypeClass *tag_type = TagTypeClass::From_Name(strtok(0, ","));
                    if (tag_type) {
                        TagClass *tag = TagClass::Find_Or_Make(tag_type);
                        if (tag) unit->Attach_Tag(tag);
                    }
                    char *token = strtok(0, ",");
                    if (token) unit->unknown_118.Unknown_00713590(atoi(token));
                    token = strtok(0, ",");
                    if (token) unit->unknown_1ac = atoi(token);
                    token = strtok(0, ",");
                    if (token) {
                        unit->unknown_79 = atoi(token) != 0;
                        if (unit->unknown_79) coord.Z = Map.Unknown_0055A280(coord) + unknown_bridge_height_ad057c;
                    }
                    token = strtok(0, ",");
                    if (token) {
                        int linked_index = atoi(token);
                        links.Add(linked_index);
                    }
                    token = strtok(0, ",");
                    if (token) unit->unknown_379 = atoi(token) != 0;
                    token = strtok(0, ",");
                    if (token) unit->unknown_37a = atoi(token) != 0;
                    if (unit->unknown_slot53(&coord, direction)) {
                        UnitTypeClass *type = Unit_Read_Float_Health_00706AE0(*unit, (float)health);
                        if (unit->Strength > type->MaxStrength - 3) unit->Strength = type->MaxStrength;
                        if (unit->Strength == 0) unit->Strength = 1;
                        unit->unknown_70 = unit->Strength;
                        if (unknown_game_mode_a3d298 == 0 || unit->House->Unknown_004F52F0()) {
                            unit->unknown_slot116(mission, false);
                            if (unit->unknown_slot122()) unit->unknown_slot117();
                        } else {
                            unit->unknown_slot261(false, true);
                        }
                    } else {
                        delete unit;
                    }
                }
            }
        }
    }
    for (int link_index = 0; link_index < Units.Count(); link_index++) {
        unsigned linked_link_index = (unsigned)links[link_index];
        Resolve_Unit_Link(link_index,linked_link_index);
    }
}
