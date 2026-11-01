// Find a cell where a factory client can leave; original0044A400.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
extern "C" Cell const exit_cell_none_0084ed10;
// @ref _exit_cell_none_0084ed10=0084ed10
Cell BuildingClass::unknown_slot280(TechnoClass *object)
{
    Cell origin = unknown_slot104();
    Cell cell;
    if (Type->GDIBarracks) {
        cell = origin + Cell(1, 2);
        if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
            return cell;
    }
    if (Type->NODBarracks) {
        cell = origin + Cell(2, 2);
        if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
            return cell;
    }
    if (Type->Naval && Type->WeaponsFactory) {
        Cell dock = Cell(unknown_slot41((int)object));
        cell = dock;
        cell += Cell(1, 1);
        if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 0) == 0)
            return cell;
        --cell.Y;
        if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 0) == 0)
            return cell;
        ++cell.Y;
        --cell.X;
        if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 0) == 0)
            return cell;
    }
    Cell const *offset = Type->FoundationOutside;
    if (!offset || Type->Hospital) {
        int bottom = Type->Foundation_Height(false);
        for (int x = -1; x <= Type->Width(); ++x) {
            cell = origin + Cell(x, bottom);
            if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
                return cell;
            cell = origin + Cell(x, -1);
            if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
                return cell;
        }
        int right = Type->Width();
        for (int y = -1; y <= Type->Foundation_Height(false); ++y) {
            cell = origin + Cell(right, y);
            if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
                return cell;
            cell = origin + Cell(-1, y);
            if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0)
                return cell;
        }
    } else {
        while (offset->X != 0x7fff || offset->Y != 0x7fff) {
            cell = origin + *offset++;
            if (Map.Unknown_0054AAB0(cell) && object->unknown_slot101(&Map[cell], -1, -1, 0, 0) == 0)
                return cell;
        }
    }
    return exit_cell_none_0084ed10;
}
