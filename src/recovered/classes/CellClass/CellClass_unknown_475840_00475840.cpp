// bool CellClass::unknown_475840(int overlay, int facing) const (0x00475840):
// whether a wall of the overlay type joins this cell toward facing: the cell
// holds the same overlay; for no overlay (-1), it holds overlay 2 or 0x1A; for
// overlays 2 and 0 a living GDI gate across facing (GDIGateOne for facings 2
// and 6, GDIGateTwo for 0 and 4) or a wall tower stands here; for 0x1A a Nod
// gate does (hypothesis from the Rules types).
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

bool CellClass::unknown_475840(int overlay, int facing) const
{
    if (OverlayIndex == overlay && OverlayIndex != -1) {
        return true;
    }
    if (overlay == -1) {
        if (OverlayIndex == 2 || OverlayIndex == 0x1A) {
            return true;
        }
    } else {
        if (overlay == 2 || overlay == 0) {
            for (ObjectClass *object = OccupierPtr; object != 0; object = object->unknown_30) {
                if (object->Kind_Of() == 6) {
                    BuildingTypeClass *type = ((BuildingClass *)object)->Type;
                    if (object->Strength > 0
                        && ((type == Rules->unknown_77c && (facing == 2 || facing == 6))
                            || (type == Rules->unknown_780 && (facing == 0 || facing == 4))
                            || type == Rules->unknown_78c)) {
                        return true;
                    }
                }
            }
        }
        if (overlay == 0x1A) {
            for (ObjectClass *object = OccupierPtr; object != 0; object = object->unknown_30) {
                if (object->Kind_Of() == 6) {
                    BuildingTypeClass *type = ((BuildingClass *)object)->Type;
                    if (object->Strength > 0
                        && ((type == Rules->unknown_784 && (facing == 2 || facing == 6))
                            || (type == Rules->unknown_788 && (facing == 0 || facing == 4)))) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
