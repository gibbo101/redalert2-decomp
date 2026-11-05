// MapRegionClass *__fastcall MapRegionClass::Create_Region_From_Cell_0056e100(CellClass *cell_ptr) (0x0056E100, RET0): floods
// out from a cell over neighbours of its height and water character into a new region. A dry patch under 75 cells is
// merged into a neighbouring region instead (returns 0). TibSun twin: mapgen.cpp MapRegionClass::Create_Region_From_Cell.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/random2.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/map_random.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?unknown_adjacent_851a70@@3QBVCell@@B=00851a70
// @ref ?unknown_map_region_next_index_a70a28@@3HA=00a70a28
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __ftol=0077f110
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ??9Cell@@QBE_NABV0@@Z=0058db50
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490

static inline Cell Region_Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + unknown_adjacent_851a70[facing & 7];
}

static inline bool Flood_In_Bounds(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;
    if (y + x > unknown_map_min_a70a1c && x - y < unknown_map_min_a70a1c &&
        y - x < unknown_map_min_a70a1c && y + x <= unknown_map_max_a70a20) {
        return true;
    }
    return false;
}

static inline void Set_Spread(Cell const &cell, int spread)
{
    MapRegionClass::Get_Cell_Data(cell).unknown_3c = spread;
}

static inline void Set_Region(Cell const &cell, int region)
{
    if (unknown_map_cells_a70a24 != 0) {
        UnknownMapGenerationCell &data = MapRegionClass::Get_Cell_Data(cell);
        data.RegionIndex = region;
    }
}

static inline unsigned Pick_Random_UInt(unsigned minimum, unsigned maximum)
{
    unsigned value;
    do {
        value = (unsigned)((unsigned)unknown_map_random_a705c0() * (1.0 / 4294967295.0) * (unsigned)(maximum + 1) + (double)minimum);
    } while (value > maximum);
    return value;
}

static inline Cell Offset_Cell(Cell cell, int dx, int dy)
{
    return Cell(cell.X + dx, cell.Y + dy);
}

static inline int Region_Of(Cell const &cell)
{
    if (unknown_map_cells_a70a24 == 0) {
        return -1;
    }
    UnknownMapGenerationCell &data = MapRegionClass::Get_Cell_Data(cell);
    return data.RegionIndex;
}

MapRegionClass *__fastcall MapRegionClass::Create_Region_From_Cell_0056e100(CellClass *cell_ptr)
{
    int i;
    int region_id = unknown_map_region_next_index_a70a28;

    DynamicVectorClass<Cell> cells;
    cells.Set_Growth_Step(50000);
    cells.Add(cell_ptr->Fetch_CellID());

    bool has_water = cell_ptr->unknown_47b7e0() || cell_ptr->unknown_47b9c0();
    int cell_height = cell_ptr->unknown_11b;
    int processed_count = 0;

    while (cells.Count()) {
        Cell cell = cells[cells.ActiveCount - 1];
        cells.Delete(cells.ActiveCount - 1);

        Set_Spread(cell, region_id);
        Set_Region(cell, region_id);

        Cell ncell;
        for (i = 0; i < 8; i++) {
            ncell = Region_Adjacent_Cell(cell, i);
            UnknownMapGenerationCell &ndata = MapRegionClass::Get_Cell_Data(ncell);
            if (Flood_In_Bounds(ncell)) {
                if (ndata.RegionIndex == -1 && ndata.unknown_3c != region_id) {
                    ndata.unknown_3c = region_id;
                    if (Map[ncell].unknown_11b == cell_height) {
                        int n_has_water = Map[ncell].unknown_47b7e0() || Map[ncell].unknown_47b9c0();
                        if (!(has_water ^ n_has_water)) {
                            cells.Add(ncell);
                        }
                    }
                }
            }
        }
        processed_count++;
    }

    if (processed_count < 75 && !has_water) {
        bool reset_done = false;

        if (region_id == 0) {
            DynamicVectorClass<Cell> *region_cells = unknown_map_generator_a6fd68.Build_Region_Border_Cell_List_00581ee0(0);
            Cell region_cell = (*region_cells)[Pick_Random_UInt(0, region_cells->Count() - 1)];

            Cell ncell;
            for (i = 0; i < 8; i++) {
                ncell = Region_Adjacent_Cell(region_cell, i);
                if (Flood_In_Bounds(ncell)) {
                    if (Map[ncell].unknown_11b != Map[region_cell].unknown_11b && !Map[ncell].unknown_47b7e0()) {
                        int height = Map[ncell].unknown_11b;

                        unknown_map_generator_a6fd68.Remap_Region_Tiles_0057e060(0, -1, height, 0);

                        reset_done = true;
                        break;
                    }
                }
            }

            delete region_cells;
        } else {
            Cell side_cell;
            side_cell = Offset_Cell(cell_ptr->Fetch_CellID(), -1, 0);
            if (!Flood_In_Bounds(side_cell)) {
                side_cell = Offset_Cell(cell_ptr->Fetch_CellID(), 0, -1);
            }

            if (Flood_In_Bounds(side_cell)) {
                int id = Region_Of(side_cell);
                int height = Map[side_cell].unknown_11b;

                unknown_map_generator_a6fd68.Remap_Region_Tiles_0057e060(region_id, id, height, 0);

                reset_done = true;
            }
        }

        if (reset_done) {
            return 0;
        }
    }

    MapRegionClass *region = new MapRegionClass(cell_ptr->Fetch_CellID());
    region->unknown_10 = cell_height;
    region->unknown_14 = has_water;
    region->CellCount = 0;
    region->Count_Grid_Cells_0056dbd0();
    return region;
}
