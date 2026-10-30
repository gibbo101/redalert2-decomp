// void __fastcall Fill_In_Data_0065cdd0() (0x0065CDD0)
// @ref ??_C@_0M@PKKJ@GasCloudSys?$AA@=007f2048
// @ref ?Initialize_Wave_Tables_00721bf0@@YIXXZ=00721bf0
// @ref ?Unknown_0054FDA0@MapClass@@QAEXXZ=0054fda0
// @ref ?Unknown_00568B00@MapClass@@QAEXXZ=00568b00
// @ref ?unknown_gas_cloud_system_a40d20@@3PAVParticleSystemClass@@A=00a40d20
// @ref ?unknown_set_buffer_zone_0053d830@@YIXH@Z=0053d830
// @ref ?unknown_slot52@RadarClass@@UAEXABUCoordStruct@@@Z=00630320
// @ref ?unknown_tags_866160@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866160
// @ref ?unknown_tags_866238@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866238
// Completes a freshly read scenario: refreshes every building, centres the
// view on the home waypoint, makes the tags of the tag types that attach to
// the map, the world or a house, counts the house-owned tags, fills the
// silos, resets the map's cell overlays and zones, makes the gas cloud
// system and scatters ore twinkles (name from Westwood's Fill_In_Data;
// called after a scenario is read and by the map seed loader 0x0057B1FD).
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/scenario_checkpoint.hpp"
#include "shared/map_view.hpp"
#include "shared/building_class.hpp"
#include "shared/tag.hpp"
#include "shared/scenario_tags.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/tiberium.hpp"
#include "shared/cell.hpp"
#include "shared/wave.hpp"
#include "shared/particle_system.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/random.hpp"
#include "shared/unknown_geometry.hpp"

void __fastcall Fill_In_Data_0065cdd0()
{
    unknown_a40774++;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        unknown_BuildingClass_list_00a40af8[index]->unknown_slot283();
    }

    Map.Flag_To_Redraw(2);

    if (!unknown_a40d13) {
        Map.unknown_slot54(1);
        if (unknown_game_mode_a3d298 == 0) {
            Cell cell = unknown_id_source_a3d290->Waypoints[unknown_scenario_checkpoint_00855a90.Variables[0] ? unknown_id_source_a3d290->AltHomeCell : unknown_id_source_a3d290->HomeCell];
            unknown_id_source_a3d290->Views[0] = unknown_id_source_a3d290->Views[1] =
                unknown_id_source_a3d290->Views[2] = unknown_id_source_a3d290->Views[3] = cell;
            CoordStruct coord = Cell_Center(cell);
            coord.Z = Map.Unknown_0055A280(coord);
            Map.unknown_slot52(coord);
        }
    }

    for (int tag_index = 0; tag_index < unknown_TagTypeClass_list_00abfea0.Count(); tag_index++) {
        TagTypeClass *tagtype = unknown_TagTypeClass_list_00abfea0[tag_index];
        if (tagtype->unknown_func_6b4c00() & 4) {
            unknown_tags_866238.Add(TagClass::Find_Or_Make(tagtype));
        }
        if (tagtype->unknown_func_6b4c00() & 0x10) {
            unknown_tags_866160.Add(TagClass::Find_Or_Make(tagtype));
        }
        if (tagtype->unknown_func_6b4c00() & 8) {
            TagClass *tag = TagClass::Find_Or_Make(tagtype);
            HouseClass *house = HouseClass::As_Pointer(((HouseTypeClass *)tag->Class->Triggers->unknown_a4)->House);
            if (house != 0) {
                house->unknown_38.Add(tag);
            }
        }
    }
    unknown_a40774--;

    for (int count_index = 0; count_index < unknown_TagTypeClass_list_00abfea0.Count(); count_index++) {
        TagTypeClass *tagtype = unknown_TagTypeClass_list_00abfea0[count_index];
        if (tagtype->unknown_func_6b4c30()) {
            HouseClass *owner = HouseClass::As_Pointer(((HouseTypeClass *)tagtype->Triggers->unknown_a4)->ArrayIndex);
            owner->unknown_1c4++;
        }
    }

    if (unknown_id_source_a3d290->FillSilos) {
        for (int house_index = 0; house_index < Houses.Count(); house_index++) {
            HouseClass *house = Houses[house_index];
            if (house != 0) {
                int money = house->Available_Money();
                TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[0];
                while (money > tiberium->Value && house->Available_Storage() > 0) {
                    house->Harvested(1.0f, 0);
                    money -= tiberium->Value;
                }
            }
        }
    }

    Map.Unknown_0049DE00(true, false);
    Initialize_Wave_Tables_00721bf0();
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        cell->Unknown_00472540(-1);
    }
    Map.Unknown_0054FDA0();
    Map.Unknown_0054EBD0();
    Map.Unknown_00563D40();
    Map.Unknown_00568B00();

    if (unknown_gas_cloud_system_a40d20 == 0) {
        unknown_gas_cloud_system_a40d20 = new ParticleSystemClass(
            ParticleSystemTypes[ParticleSystemTypeClass::Index_Or_Make("GasCloudSys")],
            CoordStruct(0xA80, 0xA80, 0), 0, 0, unknown_geometry_l);
    }

    if (Rules->OreTwinkle != 0) {
        Map.Unknown_0055A550();
        for (CellClass *ore = Map.Unknown_0055A490(); ore != 0; ore = Map.Unknown_0055A490()) {
            if (ore->Get_Tiberium_Value() && Random_Pick(0, Rules->OreTwinkleChance - 1) == 0) {
                new AnimClass(Rules->OreTwinkle, ore->Center_Coord(), 0, 1, 0x600, 0);
            }
        }
    }

    unknown_set_frame_rate_0053d820(Rules->DetailMinFrameRateNormal);
    unknown_set_buffer_zone_0053d830(Rules->DetailBufferZoneWidth);
}
