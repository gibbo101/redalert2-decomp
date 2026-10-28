// BuildingClass *BaseClass::Get_Building(int index) const (0x0042C0A0)
// The house's building standing on a node (TS BASE.CPP Get_Building): its
// type, or, for an upgrade node, a building carrying more upgrades of that
// type than the earlier nodes at the same cell account for.
#include "shared/base.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

BuildingClass *BaseClass::Get_Building(int index) const
{
    Cell cell = Nodes[index].Cell;
    if ((cell.X != 0 || cell.Y != 0) && Nodes[index].Type >= 0) {
        BuildingTypeClass *type = BuildingTypes[Nodes[index].Type];
        BuildingClass *building = (BuildingClass *)Map[cell].unknown_4717b0();
        if (building != 0 && building->unknown_slot104() == Nodes[index].Cell && building->House == House) {
            if (building->Type == type) {
                return building;
            }
            if (type->PowersUpBuilding[0]) {
                int count = 0;
                for (int upgrade = 0; upgrade < 3; upgrade++) {
                    if (building->unknown_4c0[upgrade] == type) {
                        count++;
                    }
                }
                for (int previous = 0; previous < index; previous++) {
                    if (Nodes[previous].Type >= 0 && BuildingTypes[Nodes[previous].Type] == type) {
                        CoordStruct coord = building->Coord;
                        if (Nodes[previous].Cell == Coord_Cell(coord)) {
                            count--;
                        }
                    }
                }
                return count > 0 ? building : 0;
            }
        }
    }
    return 0;
}
