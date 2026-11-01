#include "shared/foot.hpp"
#include "shared/map_view.hpp"

// Register an arriving foot in its current spatial bin.
void UnknownTracker839EA0::Unknown_004131E0(FootClass *foot)
{
    Cell cell=foot->unknown_slot104();
    foot->unknown_slot179(cell);
    Bins[Region_Index_00412820(cell)].Add(foot);
}
