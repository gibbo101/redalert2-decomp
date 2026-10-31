// int MapClass::Unknown_0055D410(CellClass *cellptr, int control) (0x0055D410)
// The map generator's water mask of a cell (TibSun Get_Water_Mask): 0 outside the
// generator's diagonal bounds, for control 0 on a cell with a tile (0x0047B590), for
// control 1 on a water tile (14 tiles from unknown_tileset_a52580), or when its
// generator record is outside the fill reach (+0x4A); the record's mask (+0x40) when
// known; else one bit per neighbour that is water (0x0047A270), a missing neighbour
// counting as water when the cell itself is.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_region.hpp"
#include "shared/tileset_index.hpp"
// My_In_Radar and Get_Cell_Data_0056dba0 are declared in 0x0055C520's source (this unit).
// @ref ?Get_Cell_Data_0056dba0@@YIAAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0

int MapClass::Unknown_0055D410(CellClass *cellptr, int control)
{
    int mask = 0;
    Cell cell = cellptr->Fetch_CellID();
    int water_start = unknown_tileset_a52580;
    int water_end = water_start + 14;
    bool is_water = cellptr->unknown_47a270();
    int x = cell.X;
    int y = cell.Y;

    if (!My_In_Radar(cell)) {
        return mask;
    }

    if (control == 0) {
        if (!cellptr->unknown_47b590()) {
            return mask;
        }
    } else if (control == 1) {
        if (cellptr->IsoTileIndex >= water_start && cellptr->IsoTileIndex < water_end) {
            return mask;
        }
    }

    UnknownMapGenerationCell &data = Get_Cell_Data_0056dba0(cellptr->Fetch_CellID());
    if (!data.unknown_45[5]) {
        return mask;
    }

    if (data.unknown_40 >= 0) {
        return data.unknown_40;
    }

    CellClass **cptr = &Cells[x + y * 512 - 512 - 1];
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x40;
    }
    cptr += 1;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x80;
    }
    cptr += 1;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x01;
    }
    cptr += 512 - 2;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x20;
    }
    cptr += 2;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x02;
    }
    cptr += 512 - 2;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x10;
    }
    cptr += 1;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x08;
    }
    cptr += 1;
    if ((cptr[0] && cptr[0]->unknown_47a270()) || (!cptr[0] && is_water)) {
        mask |= 0x04;
    }
    return mask;
}
