// bool HouseClass::unknown_func_4f5d30(int node) (0x004F5D30)
// Walls in a planned building: finds the house side's concrete wall type (Rules
// ConcreteWalls, AIBasePlanningSide), walks the base nodes back from `node` to the
// last built building that wants a wall (ProtectWithWall) and is not already followed
// by a wall node, then inserts wall nodes after it around its foundation: both long
// sides, both short sides, then the four corners. Answers whether it planned any.
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house_type.hpp"
// @ref ?Get_Building@BaseClass@@QBEPAVBuildingClass@@H@Z=0042c0a0
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Insert_After@?$DynamicVectorClass@VBaseNodeClass@@@@QAE_NABVBaseNodeClass@@H@Z=004f7270
// @ref ??0BaseNodeClass@@QAE@HABVCell@@@Z=004f6be0
// @ref ??0Cell@@QAE@HH@Z=0042ad30
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref _memmove=00783290

bool HouseClass::unknown_func_4f5d30(int node)
{
    int wall = -1;
    for (int i = 0; i < Rules->ConcreteWalls.Count(); i++) {
        if (Rules->ConcreteWalls[i]->AIBasePlanningSide == Type->Side || Rules->ConcreteWalls[i]->AIBasePlanningSide == -1) {
            wall = Rules->ConcreteWalls[i]->ArrayIndex;
            break;
        }
    }

    BuildingClass *building = 0;
    int index;
    for (index = node - 1; index >= 0; index--) {
        building = unknown_55f0.Get_Building(index);
        if (building && building->Type->ProtectWithWall && unknown_55f0.Nodes[index + 1].Type != wall) break;
    }

    if (index == -1 || !building || !building->Type->ProtectWithWall) {
        return false;
    }

    CoordStruct coord = building->Coord;
    Cell cell(coord.X / 256, coord.Y / 256);
    BuildingTypeClass *type = building->Type;
    int width = type->Width();
    int height = type->Foundation_Height(false);
    Cell corner = cell - Cell(1, 1);

    for (node = 1; node <= width; node++) {
        unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(node, 0)), index);
        unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(node, height + 1)), index);
    }
    for (node = 1; node <= height; node++) {
        unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(0, node)), index);
        unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(width + 1, node)), index);
    }

    unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(0, 0)), index);
    unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(width + 1, 0)), index);
    unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(0, height + 1)), index);
    unknown_55f0.Nodes.Insert_After(BaseNodeClass(wall, corner + Cell(width + 1, height + 1)), index);
    return true;
}
