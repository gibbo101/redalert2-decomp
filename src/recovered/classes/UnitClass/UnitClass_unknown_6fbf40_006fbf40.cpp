// void UnitClass::unknown_6fbf40() (0x006FBF40; TibSun UnitClass::Visceroid_AI):
// steps the idle animation, sends a small visceroid to merge with a neighbouring
// one, otherwise wanders to a random (or the remembered) adjacent cell.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_5d47d0@ObjectClass@@QAEHXZ=005d47d0
// The cell next to `cell` toward an 8-way facing (TibSun Adjacent_Cell; here
// the cell is taken by value, which orders the sum's loads as the original).
inline Cell Unit_Adjacent_Cell(Cell cell, int facing)
{
    return AdjacentCell[facing & 7] + cell;
}

void UnitClass::unknown_6fbf40()
{
    Cell position = unknown_slot104();
    if (StageClass::Stage >= 90) {
        if (StageClass::Stage % 5 != 4) return;
        StageClass::Stage = unknown_id_source_a3d290->Random()(0, 2) * 30;
        StageClass::Set_Rate(1);
        return;
    }
    if (StageClass::Stage % 30 == 29) {
        StageClass::Stage = unknown_id_source_a3d290->Random()(0, 2) * 30;
    }
    StageClass::Set_Rate(1);
    if (Locomotor.Checked()->Is_Moving()) return;
    if (Type->SmallVisceroid) {
        int direction = 7;
        for (int index = 0; index < 8; index++) {
            direction = (direction + 1) & 7;
            ObjectClass *object = Map[Unit_Adjacent_Cell(position, direction)].OccupierPtr;
            if (object && object->Kind_Of() == 1 && ((UnitClass *)object)->Type->SmallVisceroid) {
                UnitClass *other = (UnitClass *)object;
                if (other->unknown_494 || other->unknown_228) return;
                other->unknown_slot260(this, 1);
                unknown_5bc = -1;
                return;
            }
        }
    }
    if (unknown_494 || unknown_228) return;
    int direction;
    if (unknown_5bc == -1 || unknown_id_source_a3d290->Random()(0, 2) == 0) {
        direction = unknown_id_source_a3d290->Random()(0, 7);
        unknown_5bc = direction;
    } else {
        direction = unknown_5bc;
    }
    CellClass *destination = &Map[Unit_Adjacent_Cell(position, direction)];
    if (unknown_slot101(destination, direction, unknown_5d47d0(), (int)&Map[position], 1) == 0) {
        unknown_slot260(destination, 1);
        return;
    }
    unknown_5bc = -1;
}
