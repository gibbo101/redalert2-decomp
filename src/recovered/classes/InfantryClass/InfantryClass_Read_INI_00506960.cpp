// Creates scenario infantry from the [Infantry] records (0x00506960).
#include "shared/infantry.hpp"
#include "shared/ccini_class.hpp"
#include "shared/techno_map.hpp"
#include "shared/tag.hpp"
#include "shared/tag_type.hpp"
// @ref ?unknown_infantry_section_7a33f0@@3PBDB=007a33f0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?unknown_infantry_spots_850e50@@3QBUCoordStruct@@B=00850e50
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_bridge_height_a41120@@3HA=00a41120
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Find_Index@HouseClass@@SIHPBD@Z=004f5b40
// @ref ?From_Name@InfantryTypeClass@@SIHPBD@Z=0050a070
// @ref ?Mission_From_Name@MissionClass@@SIHPBD@Z=00594fe0
// @ref ?From_Name@TagTypeClass@@SIPAV1@PBD@Z=006b4880
// @ref ?Find_Or_Make@TagClass@@SIPAV1@PAVTagTypeClass@@@Z=006b3d30
// @ref ?Unknown_00713590@UnknownTechnoPair@@QAEXH@Z=00713590
extern char const *unknown_infantry_section_7a33f0;
extern int unknown_ini_format_a40d24;
extern CoordStruct const unknown_infantry_spots_850e50[];
extern CellClass unknown_dummy_cell_a6f9f8;
inline CoordStruct Infantry_Subcell_Position(CoordStruct center, int spot)
{
    CoordStruct aligned((center.X / 256) * 256, (center.Y / 256) * 256, center.Z);
    return aligned + unknown_infantry_spots_850e50[spot];
}
void __fastcall InfantryClass::Read_INI(CCINIClass &ini)
{
    int count = ini.Entry_Count(unknown_infantry_section_7a33f0);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_infantry_section_7a33f0, index);
        char buffer[128];
        ini.Get_String(unknown_infantry_section_7a33f0, entry, 0, buffer, sizeof(buffer));
        int house_index = HouseClass::Find_Index(strtok(buffer, ","));
        if (house_index != -1) {
            HouseClass *house = Houses[house_index];
            int type_index = InfantryTypeClass::From_Name(strtok(0, ","));
            if (type_index != -1) {
                InfantryClass *infantry = new InfantryClass(InfantryTypes[type_index], house);
                if (infantry != 0) {
                    int health = atoi(strtok(0, ","));
                    CoordStruct coord;
                    if (unknown_ini_format_a40d24 >= 4) {
                        int x = atoi(strtok(0, ","));
                        short y = (short)atoi(strtok(0, ","));
                        coord = Cell_Coord(Cell((short)x, y));
                    } else {
                        int packed = atoi(strtok(0, ","));
                        coord = Cell_Coord(Cell((short)(packed % 128), (short)(packed / 128)));
                    }
                    int spot = atoi(strtok(0, ","));
                    coord = Infantry_Subcell_Position(coord, spot);
                    int mission = MissionClass::Mission_From_Name(strtok(0, ","));
                    char *token = strtok(0, ",");
                    int direction = token != 0 ? atoi(token) : 0;
                    token = strtok(0, ",");
                    if (token != 0) {
                        TagTypeClass *tag_type = TagTypeClass::From_Name(token);
                        if (tag_type != 0) {
                            TagClass *tag = TagClass::Find_Or_Make(tag_type);
                            if (tag != 0) {
                                infantry->Attach_Tag(tag);
                            }
                        }
                    }
                    token = strtok(0, ",");
                    if (token != 0) {
                        infantry->unknown_118.Unknown_00713590(atoi(token));
                    }
                    token = strtok(0, ",");
                    if (token != 0) {
                        infantry->unknown_1ac = atoi(token);
                    }
                    token = strtok(0, ",");
                    if (token != 0) {
                        infantry->unknown_79 = atoi(token) != 0;
                        if (infantry->unknown_79) {
                            coord.Z = Map.Unknown_0055A280(coord) + unknown_bridge_height_a41120;
                        } else {
                            coord.Z = Map.Unknown_0055A280(coord);
                        }
                    }
                    token = strtok(0, ",");
                    if (token != 0) {
                        infantry->unknown_379 = atoi(token) != 0;
                    }
                    token = strtok(0, ",");
                    if (token != 0) {
                        infantry->unknown_37a = atoi(token) != 0;
                    }
                    if (&Map[coord] == &unknown_dummy_cell_a6f9f8 || !infantry->unknown_slot53(&coord, direction)) {
                        delete infantry;
                    } else {
                        InfantryTypeClass *type = infantry->Type;
                        double scaled_health = (double)health * (1.0 / 256.0);
                        scaled_health *= type->MaxStrength;
                        infantry->Strength = (int)scaled_health;
                        if (infantry->Strength > type->MaxStrength - 3) {
                            infantry->Strength = type->MaxStrength;
                        }
                        if (infantry->Strength < 1) {
                            infantry->Strength = 1;
                        }
                        infantry->unknown_70 = infantry->Strength;
                        if (unknown_game_mode_a3d298 == 0 || infantry->House->Unknown_004F52F0()) {
                            infantry->unknown_slot116(mission, false);
                            infantry->unknown_slot117();
                        } else {
                            infantry->unknown_slot261(false, true);
                        }
                    }
                }
            }
        }
    }
}
