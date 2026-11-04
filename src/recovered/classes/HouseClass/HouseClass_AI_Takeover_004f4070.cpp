// @ref ??_C@_08CJPC@Computer?$AA@=007daa28
// @ref ??_C@_0N@LAJB@TXT_COMPUTER?$AA@=007d1634
// @ref ??_C@_03JACL@GDI?$AA@=007daa24
// void HouseClass::unknown_func_4f4070() (0x004F4070): the AI takes over this house (TibSun AI_Takeover):
// name, factories, handicap, base centre, then rebuilds the base nodes from the buildings it owns.
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/cell_class.hpp"
#include "shared/map.hpp"
#include "shared/overlay_type.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/ini_class.hpp"
// A computer house in a network game. The query is one level down here: the original calls
// Unknown_004F52B0 out of line at this site and expands it at the first one.
inline bool Is_Network_Computer(HouseClass *house)
{
    return !house->unknown_func_4f52f0() && unknown_game_mode_a3d298 != 0;
}
void HouseClass::unknown_func_4f4070()
{
    if (!unknown_func_4f52f0()) return;
    unknown_134=false;
    unknown_135=false;
    unknown_194=Rules->MaxIQ;
    IniName=FixedString<21>("Computer");
    wcscpy(UIName,StringTable::Load_String("TXT_COMPUTER",0,"D:\\Ra2\\House.CPP",0x3130));
    int index;
    for (index=Factories.Count()-1;index>=0;--index) {
        FactoryClass *factory=Factories[index];
        if (factory->Owner==this) {
            Factories[index]->Suspend_004B9630(true);
            Factories[index]->Abandon_Production_004B97C0();
            delete Factories[index];
        }
    }
    Assign_Handicap(2-unknown_c8);
    BuildingClass *conyard=0;
    for (index=Buildings.Count()-1;index>=0;--index) {
        BuildingClass *building=Buildings[index];
        bool owned_type=false;
        for (int candidate=0;candidate<Rules->unknown_7c8.Count();++candidate) {
            if (Rules->unknown_7c8[candidate]==building->Type) { owned_type=true; break; }
        }
        if (!owned_type) continue;
        if (!building->unknown_76) { conyard=building; break; }
    }
    if (!conyard) return;
    Cell center=Coord_Cell(conyard->Position_Coord_004f3f40());
    BaseCenter=Cell_Coord(center);
    if (Is_Network_Computer(this)) unknown_func_4ec5e0();
    if (unknown_55f0.Nodes.Count()==0) {
        int saved_init=unknown_a40774;
        unknown_a40774=0;
        unknown_func_4ef890();
        unknown_a40774=saved_init;
    }
    unknown_55f0.Nodes[0].Cell=center;
    unknown_55f0.unknown_50=center;
    unknown_136=true;
    unknown_13a=true;
    unknown_13b=true;
    for (int node=unknown_55f0.Nodes.Count()-1;node>=0;--node) {
        int type=unknown_55f0.Nodes[node].Type;
        if (type>=0 && unknown_5460.unknown_func_491d10(type)>0) {
            BuildingTypeClass *building_type=BuildingTypes[type];
            for (int owned=Buildings.Count()-1;owned>=0;--owned) {
                BuildingClass *building=Buildings[owned];
                if (!building->unknown_76 && (building->Type==building_type
                    || building->unknown_4c0[0]==building_type || building->unknown_4c0[1]==building_type
                    || building->unknown_4c0[2]==building_type)) {
                    unknown_55f0.Nodes[node].Cell=Coord_Cell(building->Position_Coord_004f3f40());
                }
            }
        }
    }
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while (cell) {
        if (cell->unknown_50==ArrayIndex && cell->OverlayIndex!=-1 && OverlayTypes[cell->OverlayIndex]->Wall) {
            Sell_Wall(cell->MapCoords,true);
        }
        cell=Map.Unknown_0055A490();
    }
    int building_count=Buildings.Count();
    int defense_node=0;
    for (index=0;index<building_count;++index) {
        BuildingClass *building=Buildings[index];
        if (building->unknown_76) continue;
        BuildingTypeClass *building_type=building->Type;
        if (!building_type->IsBaseDefense && !(building_type==Rules->unknown_78c && building->unknown_5c6>0)) continue;
        if (!building_type->Who_Can_Build_Me(true,false,true,this)) continue;
        while (defense_node<unknown_55f0.Nodes.Count()) {
            if (unknown_55f0.Nodes[defense_node].Type==-1) {
                if (building->Type==Rules->unknown_78c) {
                    unknown_55f0.Nodes.Insert_After(BaseNodeClass(
                        ((BuildingTypeClass *)building->unknown_4c0[building->unknown_5c6-1])->ArrayIndex,
                        Coord_Cell(building->Position_Coord_004f3f40())),defense_node);
                    unknown_55f0.Nodes[defense_node].Type=building->Type->ArrayIndex;
                    unknown_55f0.Nodes[defense_node].Cell=Coord_Cell(building->Position_Coord_004f3f40());
                    ++defense_node;
                } else {
                    unknown_55f0.Nodes[defense_node].Type=building->Type->ArrayIndex;
                    unknown_55f0.Nodes[defense_node].Cell=Coord_Cell(building->Position_Coord_004f3f40());
                }
                ++defense_node;
                break;
            }
            ++defense_node;
        }
    }
    int power_node=0;
    int power=0;
    int drain=0;
    building_count=Buildings.Count();
    for (index=0;index<building_count;++index) {
        BuildingClass *building=Buildings[index];
        if (building->unknown_76) continue;
        BuildingTypeClass *building_type=building->Type;
        if (building_type!=Rules->GDIPowerPlant && building_type!=Rules->NodRegularPower
            && building_type!=Rules->NodAdvancedPower) continue;
        if (Coord_Cell(building->Position_Coord_004f3f40())==unknown_55f0.Nodes[1].Cell) continue;
        if (!building_type->Who_Can_Build_Me(true,false,true,this)) continue;
        while (power_node<unknown_55f0.Nodes.Count()) {
            if (unknown_55f0.Nodes[power_node].Type>=0) {
                BuildingTypeClass *planned_type=BuildingTypes[unknown_55f0.Nodes[power_node].Type];
                power+=planned_type->Power;
                drain+=planned_type->PowerDrain_c6c;
                if (power_node>0 && power<drain+unknown_15f88) {
                    unknown_55f0.Nodes.Insert_After(BaseNodeClass(building->Type->ArrayIndex,
                        Coord_Cell(building->Position_Coord_004f3f40())),power_node-1);
                    power+=building->Type->Power;
                    drain-=planned_type->PowerDrain_c6c;
                    ++power_node;
                    break;
                }
            }
            ++power_node;
        }
    }
    if (_stricmp(Type->ID,"GDI")==0) {
        power_node=0;
        power=0;
        drain=0;
        for (index=0;index<unknown_BuildingClass_list_00a40af8.Count();++index) {
            BuildingClass *building=unknown_BuildingClass_list_00a40af8[index];
            if (building->House!=this || building->unknown_76 || building->Type!=Rules->GDIPowerPlant
                || building->unknown_5c6<=0) continue;
            for (int upgrade=0;upgrade<building->unknown_5c6;++upgrade) {
                while (power_node<unknown_55f0.Nodes.Count()) {
                    if (unknown_55f0.Nodes[power_node].Type>=0) {
                        BuildingTypeClass *planned_type=BuildingTypes[unknown_55f0.Nodes[power_node].Type];
                        power+=planned_type->Power;
                        drain+=planned_type->PowerDrain_c6c;
                        if (power_node>0 && power<drain+unknown_15f88) {
                            unknown_55f0.Nodes.Insert_After(BaseNodeClass(Rules->GDIPowerTurbine->ArrayIndex,
                                Coord_Cell(building->Position_Coord_004f3f40())),power_node-1);
                            power+=Rules->GDIPowerTurbine->Power;
                            drain-=planned_type->PowerDrain_c6c;
                            ++power_node;
                            break;
                        }
                    }
                    ++power_node;
                }
            }
        }
    }
}
