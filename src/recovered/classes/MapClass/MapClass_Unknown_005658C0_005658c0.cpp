// int MapClass::Unknown_005658C0(int &zone) (0x005658C0)
// Counts the zones (0x0054F8F0, type 10) of the local map's cells whose
// +0x4C is 4 (the walk 0x0055A910 over Map) and returns the count of the
// most common one, its zone in `zone` (-1 and 0 when none).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"

int MapClass::Unknown_005658C0(int &zone)
{
    DynamicVectorClass<int> counts;
    Map.unknown_118 = Map.MapLocalSize.Y + Map.MapLocalSize.X + 1;
    Map.unknown_11c = Map.MapSize.Width - Map.MapLocalSize.X + Map.MapLocalSize.Y;
    for (CellClass *cellptr = Map.Unknown_0055A910(); cellptr != 0; cellptr = Map.Unknown_0055A910()) {
        if (cellptr->unknown_4c == 4) {
            int z = Zone(cellptr->MapCoords, 10, false);
            if (z >= 0) {
                if (z >= counts.Count()) {
                    int need = z - counts.Count() + 1;
                    for (int index = 0; index < need; index++) {
                        counts.Add(0);
                    }
                }
                counts[z]++;
            }
        }
    }
    int best = -1;
    int most = 0;
    for (int index = 0; index < counts.Count(); index++) {
        if (counts[index] > most) {
            best = index;
            most = counts[index];
        }
    }
    zone = best;
    if (best >= 0) {
        return counts[best];
    }
    return 0;
}
