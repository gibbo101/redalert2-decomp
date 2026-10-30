#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/unknown_map_generator.hpp"
extern double const unknown_grid_weight_7a5d10,unknown_grid_scale_7a5d18,unknown_grid_weight_7a5d20;
// @ref ?unknown_grid_weight_7a5d10@@=007a5d10
// @ref ?unknown_grid_scale_7a5d18@@=007a5d18
// @ref ?unknown_grid_weight_7a5d20@@=007a5d20
// @ref __real@8@3ff8847ae147ae147800=0079c518
// @ref __real@8@4002a000000000000000=0079d130
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
static inline UnknownMapGenerationCell &Vegetation_Grid_Record(Cell const &position)
{
    unsigned at=(unsigned)(int)position.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position.X;
    return unknown_map_cells_a70a24[at];
}
// ECX owner prefix, plain RET; operation/nominal receiver spelling remain hypotheses.
void __fastcall Initialize_Vegetation_Weights_005850a0(UnknownMapGenerator *generator)
{
    Map.Unknown_0055A550();
    CellClass *current=Map.Unknown_0055A490();
    double density=generator->SeedOptions.Vegetation*0.01;
    while(current) {
        Cell position=current->MapCoords;
        UnknownMapGenerationCell &grid=Vegetation_Grid_Record(position);
        if(current->unknown_47b7c0()) {
            for(int x=Cell(current->MapCoords).X-2;x<Cell(current->MapCoords).X+3;++x) {
                for(int y=Cell(current->MapCoords).Y-2;y<Cell(current->MapCoords).Y+3;++y) {
                    Cell nearby; nearby.X=(short)x; nearby.Y=(short)y;
                    if(Generation_Cell_In_Bounds_0058da10(nearby)) {
                        grid.unknown_28=unknown_grid_weight_7a5d10;
                        double weighted=unknown_grid_scale_7a5d18*density;
                        grid.unknown_20=0.0;
                        grid.unknown_18=weighted*10.0;
                    }
                }
            }
        } else if(grid.unknown_28==0.0) {
            grid.unknown_28=unknown_grid_weight_7a5d10;
            grid.unknown_18=unknown_grid_scale_7a5d18*density;
            grid.unknown_20=unknown_grid_weight_7a5d20;
        }
        current=Map.Unknown_0055A490();
    }
}
