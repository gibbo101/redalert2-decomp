// bool TechnoTypeClass::unknown_slot42(Cell const &cell, HouseClass *house) const (0x006DE0E0, slot 42)
// Whether the type can be placed at a cell (hypothesis: Legal_Placement):
// every cell of its occupy list (slot 36) must be open for it, by
// 0x004718B0 for building types (Kind_Of 7) and 0x00478760 otherwise; a
// building type flagged at +0xBF0 needs only one open cell.
#include "shared/techno_type.hpp"
#include "shared/object.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_cell_ac01e8@@3VCell@@A=00ac01e8
// @ref ?Unknown_004718B0@UnknownPlacementCellView@@QAE_NHPBVTechnoTypeClass@@PAVHouseClass@@@Z=004718b0
// @ref ?Unknown_00478760@UnknownPlacementCellView@@QAE_NH_N0HHH0@Z=00478760

// The cell value meaning "no cell" (0x00AC01E8).
extern Cell unknown_cell_ac01e8;

// Member-wise sum of two cells: shared/coord.hpp.

// A building type's flag at +0xBF0 (view).
struct UnknownBuildingTypeBF0View {
    char unknown_000[0xBF0];
    int unknown_bf0;
};

bool TechnoTypeClass::unknown_slot42(Cell const &cell, HouseClass *house) const
{
    if (cell == unknown_cell_ac01e8) {
        return false;
    }
    Cell const *offset = unknown_slot36(1);
    bool building = Kind_Of() == 7;
    bool blocked = false;
    bool open = false;
    while (offset && *offset != Cell(0x7FFF, 0x7FFF)) {
        Cell place = cell + *offset++;
        if (building) {
            if (!((UnknownPlacementCellView &)Map[place]).Unknown_004718B0(SpeedType, this, house)) {
                blocked = true;
            } else {
                open = true;
            }
        } else {
            if (!((UnknownPlacementCellView &)Map[place]).Unknown_00478760(SpeedType, false, false, -1, 0, -1, true)) {
                blocked = true;
            } else {
                open = true;
            }
        }
    }
    if (building && ((UnknownBuildingTypeBF0View *)this)->unknown_bf0) {
        return open;
    }
    return !blocked;
}
