#include "shared/foot.hpp"
#include "shared/map_view.hpp"

// Remove a departing foot from the spatial bin recorded on it.
void UnknownTracker839EA0::Unknown_00413310(TechnoClass *foot)
{
    Cell cell=foot->unknown_slot178();
    foot->unknown_slot179(unknown_geometry_k);
    Bins[Region_Index_00412820(cell)].Delete(static_cast<TechnoClass *>(foot));
}
