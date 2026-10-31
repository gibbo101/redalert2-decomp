#include "shared/path_estimator.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tube.hpp"
#include "shared/adjacent_cell.hpp"
Cell __fastcall UnknownPathEstimator::Unknown_0042AD50(Cell const &cell, int facing)
{
    if (facing == 8) {
        int tube = Map[cell].unknown_116;
        if (tube != -1) {
            return Cell(unknown_TubeClass_list_008661c8[tube]->ExitCell);
        }
        return Cell(0, 0);
    }
    return cell + AdjacentCell[facing];
}
