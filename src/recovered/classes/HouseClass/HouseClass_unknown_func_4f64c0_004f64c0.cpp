// House node readiness, original004F64C0. Original source-independent extent224+0.
#include "shared/house.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
bool HouseClass::unknown_func_4f64c0(BaseNodeClass const &node)
{
    int type_index=node.Type;
    if (unknown_game_mode_a3d298==0) return true;
    if (type_index<0) return true;
    if (type_index>=BuildingTypes.Count()) return false;
    BuildingTypeClass *type=BuildingTypes[type_index];
    if (!type) return false;
    if (type->Get_Weapon(0)->WeaponType) return true;
    if (type->Wall) {
        for (int facing=0;facing<8;++facing) {
            CellClass &cell=Map[node.Cell];
            TechnoClass *building=(TechnoClass *)cell.Adjacent_Cell(facing).unknown_4717b0();
            if (building && building->House==this) return true;
        }
        return false;
    }
    if (type->Power>0) return true;
    if (unknown_5408+Rules->AIRestrictReplaceTime<=Frame) return true;
    return false;
}
