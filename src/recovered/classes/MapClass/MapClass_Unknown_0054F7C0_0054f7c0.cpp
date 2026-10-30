// bool MapClass::Unknown_0054F7C0(Cell const &from, Cell const &to, int zone, bool arg4,
//     bool bridge, bool arg6) (0x0054F7C0)
// Whether two cells share a movement zone (TibSun Is_Same_Cell_Zone): always
// for zone type -1, for a source on the map but outside the local view, and
// (arg6) for leaving the view onto the map; else the two cells' zones
// (0x0054F8F0 with arg4 and bridge as the bridge flags) are compared.
#include "shared/map.hpp"
#include "shared/map_view.hpp"

bool MapClass::Unknown_0054F7C0(Cell const &from, Cell const &to, int zone, bool arg4, bool bridge, bool arg6)
{
    if (zone == -1) {
        return true;
    }

    bool from_local = Map.Unknown_0055A660(from, true);
    bool from_map = Map.Unknown_0054AAB0(from);
    if (!from_local && from_map) {
        return true;
    }

    bool to_local = Map.Unknown_0055A660(to, true);
    bool to_map = Map.Unknown_0054AAB0(to);
    if (arg6 && from_local && !to_local && to_map) {
        return true;
    }

    return Zone(from, zone, arg4) == Zone(to, zone, bridge);
}
