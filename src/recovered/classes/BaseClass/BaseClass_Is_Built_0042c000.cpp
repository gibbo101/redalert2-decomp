// bool BaseClass::Is_Built(int index) const (0x0042C000)
// A node counts as built when its building stands there; a wall node also
// when its cell already holds the wall's overlay or any building (TS BASE.CPP
// Is_Built).
#define VECTOR_IMPLEMENT_ALL
#include "shared/base.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/overlay_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

bool BaseClass::Is_Built(int index) const
{
    if (Get_Building(index) != 0) {
        return true;
    }
    if (Nodes[index].Type >= 0) {
        BuildingTypeClass *type = BuildingTypes[Nodes[index].Type];
        if (type->Wall) {
            CellClass &cell = Map[Nodes[index].Cell];
            if (cell.OverlayIndex == type->ToOverlay->ArrayIndex) {
                return true;
            }
            if (cell.unknown_4717b0() != 0) {
                return true;
            }
        }
    }
    return false;
}
