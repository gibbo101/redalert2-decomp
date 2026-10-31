// bool MapClass::Expand_Water(CellClass *cellptr, int region_id, bool set_region) (0x0055C630)
// The map generator's water flood (TibSun Expand_Water): the cell's water mask (+0x40) is
// recomputed (0x0055D410, control 2); a cell whose land-side mask (control 0) shows a pinch,
// a narrow neck or water across it becomes water (+0x38 the first water tile, +0x11A = 0)
// unless another region holds it (without set_region); its region becomes region_id (or 0
// with set_region) and the flood spreads to every neighbour inside the generator bounds.
// False only when another region holds the cell.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
#include "shared/tileset_index.hpp"
#include "shared/unknown_map_generator.hpp"
// @ref ?Get_Cell_Data_0056dba0@@YIAAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
// @ref ?Unknown_0055D410@MapClass@@QAEHPAVCellClass@@H@Z=0055d410
// @ref ?Get_Cell_Data_Region_005818a0@UnknownMapGenerator@@QAEHABVCell@@@Z=005818a0
// @ref ?Set_Cell_Data_Region_00581870@UnknownMapGenerator@@QAEXABVCell@@H@Z=00581870

bool MapClass::Expand_Water(CellClass *cellptr, int region_id, bool set_region)
{
    bool expand = false;

    UnknownMapGenerationCell &data = Get_Cell_Data_0056dba0(cellptr->Fetch_CellID());
    data.unknown_40 = Unknown_0055D410(cellptr, 2);

    int mask = Unknown_0055D410(cellptr, 0);
    if (mask > 0) {

        if (mask == 0x0B || mask == 0x1A) {
            expand = true;
        }

        if ((mask & 0xA0) == 0xA0 && (mask & 0x11) == 0 ||
            (mask & 0x82) == 0x82 && (mask & 0x44) == 0 ||
            (mask & 0x0A) == 0x0A && (mask & 0x11) == 0 ||
            (mask & 0x28) == 0x28 && (mask & 0x44) == 0) {
            expand = true;
        }

        if ((mask & 0x20) != 0) {
            Cell cell1 = cellptr->Fetch_CellID() + Cell(1, 0);
            CellClass *cptr1 = &Map[cell1];
            int mask1 = Unknown_0055D410(cptr1, 0);
            Cell cell2 = cellptr->Fetch_CellID() + Cell(2, 0);
            CellClass *cptr2 = &Map[cell2];
            int mask2 = Unknown_0055D410(cptr2, 0);
            if ((mask1 & 0x02) != 0 || (mask2 & 0x02) != 0) {
                expand = true;
            }
        }

        if ((mask & 0x02) != 0) {
            Cell cell1 = cellptr->Fetch_CellID() + Cell(-1, 0);
            CellClass *cptr1 = &Map[cell1];
            int mask1 = Unknown_0055D410(cptr1, 0);
            Cell cell2 = cellptr->Fetch_CellID() + Cell(-2, 0);
            CellClass *cptr2 = &Map[cell2];
            int mask2 = Unknown_0055D410(cptr2, 0);
            if ((mask1 & 0x20) != 0 || (mask2 & 0x20) != 0) {
                expand = true;
            }
        }

        if ((mask & 0x08) != 0) {
            Cell cell1 = cellptr->Fetch_CellID() + Cell(0, -1);
            CellClass *cptr1 = &Map[cell1];
            int mask1 = Unknown_0055D410(cptr1, 0);
            Cell cell2 = cellptr->Fetch_CellID() + Cell(0, -2);
            CellClass *cptr2 = &Map[cell2];
            int mask2 = Unknown_0055D410(cptr2, 0);
            if ((mask1 & 0x80) != 0 || (mask2 & 0x80) != 0) {
                expand = true;
            }
        }

        if ((mask & 0x80) != 0) {
            Cell cell1 = cellptr->Fetch_CellID() + Cell(0, 1);
            CellClass *cptr1 = &Map[cell1];
            int mask1 = Unknown_0055D410(cptr1, 0);
            Cell cell2 = cellptr->Fetch_CellID() + Cell(0, 2);
            CellClass *cptr2 = &Map[cell2];
            int mask2 = Unknown_0055D410(cptr2, 0);
            if ((mask1 & 0x08) != 0 || (mask2 & 0x08) != 0) {
                expand = true;
            }
        }

        if ((mask & 0x88) == 0x88 || (mask & 0x22) == 0x22 || expand) {

            int cell_region_id = unknown_map_generator_a6fd68.Get_Cell_Data_Region_005818a0(cellptr->Fetch_CellID());
            if (cell_region_id > 0 && cell_region_id != region_id && !set_region) {
                return false;
            }
            cellptr->IsoTileIndex = unknown_tileset_a52580;
            cellptr->unknown_11a = 0;
            if (set_region) {
                unknown_map_generator_a6fd68.Set_Cell_Data_Region_00581870(cellptr->Fetch_CellID(), 0);
            } else {
                unknown_map_generator_a6fd68.Set_Cell_Data_Region_00581870(cellptr->Fetch_CellID(), region_id);
            }
            for (int dir = 0; dir < 8; dir++) {
                CellClass *adjptr = &cellptr->Adjacent_Cell(dir);
                if (My_In_Radar(adjptr->Fetch_CellID())) {
                    Get_Cell_Data_0056dba0(adjptr->Fetch_CellID()).unknown_40 = -1;
                    Expand_Water(adjptr, region_id, set_region);
                }
            }
        }
    }
    return true;
}
