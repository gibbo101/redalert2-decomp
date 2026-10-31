#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &);
void MapRegionClass::Mark_Rectangle_00575bf0(Rect const &area)
{
    for(int y=area.Y;y<area.Y+area.Height;++y) {
        for(int x=area.X;x<area.X+area.Width;++x) {
            Cell const position((short)x,(short)y);
            if(Generation_Cell_In_Bounds_0058da10(position)) {
                Set_Cell_Region_Index_0056e970(position,Index);
                CellClass &target=Map[position];
                target.unknown_11b=(char)unknown_10;
            }
        }
    }
}

// 0056E970: conditionally assign a map-generation grid cell's region index.
// Genuine accepted provider included as auxiliary; no new-byte credit.
// Physical contract: ECX -> signed16 X/Y, EDX -> raw32 stored at grid+38,
// RET0, no defined return value. Name, const-reference and int intent are hypotheses.
#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
void __fastcall Set_Cell_Region_Index_0056e970(Cell const &position, int index)
{
    UnknownMapGenerationCell *cells = unknown_map_cells_a70a24;
    if (cells) {
        unsigned int row = position.Y;
        row *= unknown_map_cell_side_84e804;
        unsigned int slot = position.X;
        slot = row + slot;
        cells[slot].RegionIndex = index;
    }
}
