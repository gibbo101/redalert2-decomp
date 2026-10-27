// Aircraft.cpp scenario input0041A840; static member identity is a hypothesis.
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/ccini_class.hpp"
// @ref ?unknown_aircraft_section_79b0d0@@3PBDB=0079b0d0
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd
// @ref ?Find_Index@HouseClass@@SIHPBD@Z=004f5b40
// @ref ?From_Name@AircraftTypeClass@@SIHPBD@Z=0041be60
// @ref ?Mission_From_Name@MissionClass@@SIHPBD@Z=00594fe0
// @ref ?From_Name@TagTypeClass@@SIPAV1@PBD@Z=006b4880
// @ref ?Find_Or_Make@TagClass@@SIPAV1@PAVTagTypeClass@@@Z=006b3d30
// @ref ?Unknown_00713590@UnknownTechnoPair@@QAEXH@Z=00713590
extern char const *unknown_aircraft_section_79b0d0;
extern int unknown_ini_format_a40d24;
void __fastcall AircraftClass::Read_INI_0041A840(CCINIClass &ini)
{
    int count = ini.Entry_Count(unknown_aircraft_section_79b0d0);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_aircraft_section_79b0d0, index);
        char buffer[128];
        ini.Get_String(unknown_aircraft_section_79b0d0, entry, 0, buffer, sizeof(buffer));
        int house_index = HouseClass::Find_Index(strtok(buffer, ","));
        if (house_index != -1) {
            int type_index = AircraftTypeClass::From_Name(strtok(0, ","));
            if (type_index != -1) {
                HouseClass *house = Houses[house_index];
                AircraftClass *aircraft = new AircraftClass(AircraftTypes[type_index], house);
                if (aircraft) {
                    int health = atoi(strtok(0, ","));
                    Cell cell;
                    if (unknown_ini_format_a40d24 >= 4) {
                        Cell parsed;
                        parsed.X = (short)atoi(strtok(0, ","));
                        parsed.Y = (short)atoi(strtok(0, ","));
                        cell = parsed;
                    } else {
                        int packed = atoi(strtok(0, ","));
                        cell = Cell((short)(packed % 128), (short)(packed / 128));
                    }
                    CoordStruct coord = Cell_Coord(cell);
                    int direction = atoi(strtok(0, ","));
                    int mission = MissionClass::Mission_From_Name(strtok(0, ","));
                    TagTypeClass *tag_type = TagTypeClass::From_Name(strtok(0, ","));
                    if (tag_type) {
                        TagClass *tag = TagClass::Find_Or_Make(tag_type);
                        if (tag) aircraft->Attach_Tag(tag);
                    }
                    char *token = strtok(0, ",");
                    if (token) aircraft->unknown_118.Unknown_00713590(atoi(token));
                    token = strtok(0, ",");
                    if (token) aircraft->unknown_1ac = atoi(token);
                    token = strtok(0, ",");
                    if (token) aircraft->unknown_379 = atoi(token) != 0;
                    token = strtok(0, ",");
                    if (token) aircraft->unknown_37a = atoi(token) != 0;
                    if (aircraft->unknown_slot53(&coord, direction)) {
                        AircraftTypeClass *type = aircraft->Type;
                        aircraft->Strength = (int)((double)health * (1.0 / 256.0) * type->MaxStrength);
                        if (aircraft->Strength > type->MaxStrength - 3) aircraft->Strength = type->MaxStrength;
                        if (aircraft->Strength == 0) aircraft->Strength = 1;
                        aircraft->unknown_70 = aircraft->Strength;
                        if (unknown_game_mode_a3d298 == 0 || aircraft->House->Unknown_004F52F0()) {
                            aircraft->unknown_slot116(mission, false);
                            aircraft->unknown_slot117();
                        } else aircraft->unknown_slot261(false, true);
                    } else {
                        delete aircraft;
                    }
                }
            }
        }
    }
}
