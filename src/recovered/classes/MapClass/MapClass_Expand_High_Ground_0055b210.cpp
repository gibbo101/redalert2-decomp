// bool MapClass::Expand_High_Ground(CellClass *cellptr, int region_id) (0x0055B210)
// The map generator's high-ground flood (TibSun Expand_High_Ground): a cell whose high-ground
// mask (0x0055BD70) shows a pinch, a lone raised neighbour pair, a notch or high ground across
// it is raised one step (+0x11B += 4) and joins region_id (0x00581870), unless another region
// holds it (0x005818A0; region_id -1 claims anything); the flood then spreads to all eight
// neighbours. False only when another region holds the cell.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
#include "shared/unknown_map_generator.hpp"
// @ref ?Unknown_0055BD70@MapClass@@QAEIPAVCellClass@@@Z=0055bd70
// @ref ?Get_Cell_Data_Region_005818a0@UnknownMapGenerator@@QAEHABVCell@@@Z=005818a0
// @ref ?Set_Cell_Data_Region_00581870@UnknownMapGenerator@@QAEXABVCell@@H@Z=00581870

bool MapClass::Expand_High_Ground(CellClass *cellptr, int region_id)
{
    bool expand = false;
    unsigned int mask = Unknown_0055BD70(cellptr);

    if ((mask & 0xA0) == 0xA0 && (mask & 0x11) == 0x11) {
        expand = true;
    }

    if ((mask & 0x20) != 0) {
        if ((Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 0)]) & 0x02) != 0) {
            expand = true;
        }
    }

    if ((mask & 0x02) != 0) {
        if ((Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(-1, 0)]) & 0x20) != 0) {
            expand = true;
        }
    }

    if ((mask & 0x08) != 0) {
        if ((Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(0, -1)]) & 0x80) != 0) {
            expand = true;
        }
    }

    if ((mask & 0x80) != 0) {
        if ((Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(0, 1)]) & 0x08) != 0) {
            expand = true;
        }
    }

    if ((mask & 0x11) == 0x11 &&
        ((mask & 0x0A) != 0x0A || (mask & 0xE0) != 0) &&
        ((mask & 0xA0) != 0xA0 || (mask & 0x0E) != 0)) {
        expand = true;
    }

    if ((mask & 0x44) == 0x44 &&
        ((mask & 0x28) != 0x28 || (mask & 0x83) != 0) &&
        ((mask & 0x82) != 0x82 || (mask & 0x38) != 0)) {
        expand = true;
    }

    if ((mask & 0x2C) == 0x24 ||
        (mask & 0xA1) == 0x21 ||
        (mask & 0x1A) == 0x12 ||
        (mask & 0xC2) == 0x42 ||
        (mask & 0x0B) == 0x09 ||
        (mask & 0x68) == 0x48 ||
        (mask & 0x86) == 0x84 ||
        (mask & 0xB0) == 0x90) {
        expand = true;
    }

    if ((mask & 0x88) == 0x88 || (mask & 0x22) == 0x22 || expand) {
        int cell_region_id = unknown_map_generator_a6fd68.Get_Cell_Data_Region_005818a0(cellptr->Fetch_CellID());
        if (cell_region_id > 0 && cell_region_id != region_id && region_id != -1) {
            return false;
        }
        cellptr->unknown_11b += 4;
        unknown_map_generator_a6fd68.Set_Cell_Data_Region_00581870(cellptr->Fetch_CellID(), region_id);
        for (int dir = 0; dir < 8; dir++) {
            Expand_High_Ground(&cellptr->Adjacent_Cell(dir), region_id);
        }
    }
    return true;
}
