// Begin construction from an existing construction yard, original004F5BE0;328body+8padding.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"

void HouseClass::unknown_func_4f5be0()
{
    BuildingClass *construction_yard=0;
    for (int index=Buildings.Count()-1;index>=0;--index) {
        BuildingClass *building=Buildings[index];
        bool is_construction_yard=false;
        for (int type_index=0;type_index<Rules->unknown_7c8.Count();++type_index) {
            if (Rules->unknown_7c8[type_index]==building->Type) {
                is_construction_yard=true;
                break;
            }
        }
        if (is_construction_yard && !building->unknown_76) {
            construction_yard=building;
            break;
        }
    }
    if (!construction_yard) return;
    CoordStruct position=construction_yard->Position_Coord_004f3f40();
    Cell center=Coord_Cell(position);
    BaseCenter=Cell_Coord(center);
    if (!Is_Human_Control() && unknown_game_mode_a3d298!=0) unknown_func_4ec5e0();
    if (unknown_55f0.Nodes.Count()==0) {
        int saved_initialization=unknown_a40774;
        unknown_a40774=0;
        unknown_func_4ef890();
        unknown_a40774=saved_initialization;
    }
    unknown_55f0.Nodes[0].Cell=center;
    unknown_55f0.unknown_50=center;
}
