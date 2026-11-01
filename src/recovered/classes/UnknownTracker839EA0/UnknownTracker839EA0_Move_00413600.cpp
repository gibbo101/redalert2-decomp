#include "shared/foot.hpp"
#include "shared/map_view.hpp"

// Move a foot between bins only when the spatial-bin indices change.
void UnknownTracker839EA0::Unknown_00413600(TechnoClass *foot,Cell from,Cell to)
{
    foot->unknown_slot179(to);
    int old_index=Region_Index_00412820(from);
    int new_index=Region_Index_00412820(to);
    if (old_index!=new_index) {
        Bins[old_index].Delete(static_cast<TechnoClass *>(foot));
        Bins[new_index].Add(foot);
    }
}
