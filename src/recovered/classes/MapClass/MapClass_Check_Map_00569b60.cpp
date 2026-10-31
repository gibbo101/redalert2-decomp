// bool MapClass::Check_Map() (0x00569B60)
// A debug consistency check of the zone tables (TibSun MapClass::Check_Map): for every
// map cell and every movement zone but Subterannean (6) and Fly (9), every later cell of
// the local map that the zone tables say is reachable (0x0054F7C0) ground to ground,
// bridge to bridge, ground to bridge or bridge to ground is walked by the path estimator
// (0x0042AA30); each walk that fails is written to MapCheck.txt. Whether none failed.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/path_estimator.hpp"
#include "shared/crt_stdio.hpp"
// @ref ??_C@_01LLF@w?$AA@=007e09c0
// @ref ??_C@_0N@HACB@MapCheck?4txt?$AA@=007e09b0
// @ref ??_C@_0DJ@IFGF@Failure?3?5?$CI?$CFd?0?$CFd?$CJ?9?$DO?$CI?$CFd?0?$CFd?$CJ?5?$DL?5?$CIbri@=007e08c0
// @ref ??_C@_0DJ@PBPI@Failure?3?5?$CI?$CFd?0?$CFd?$CJ?9?$DO?$CI?$CFd?0?$CFd?$CJ?5?$DL?5?$CIbri@=007e0938
// @ref ??_C@_0DJ@KFJO@Failure?3?5?$CI?$CFd?0?$CFd?$CJ?9?$DO?$CI?$CFd?0?$CFd?$CJ?5?$DL?5?$CIgro@=007e08fc
// @ref ??_C@_0DJ@NBAD@Failure?3?5?$CI?$CFd?0?$CFd?$CJ?9?$DO?$CI?$CFd?0?$CFd?$CJ?5?$DL?5?$CIgro@=007e0974
// @ref _fopen=00783a45
// @ref _fprintf=007839d8
// @ref _fclose=0078395b
// @ref ?MovementZoneNames@@3PAPBDA=007d1a68
// @ref ?unknown_table_7e00c4@@3PAY07HA=007e00c4
// @ref ?unknown_path_estimator_8315c8@@3UUnknownPathEstimator@@A=008315c8

// The movement zone names (0x007D1A68; as shared/ccini_extra.hpp, which the Map unit
// does not include).
extern char const *MovementZoneNames[12];

bool MapClass::Check_Map()
{
    bool from_ground;
    bool from_bridge;
    bool to_ground;
    bool to_bridge;
    CellClass *from;
    CellClass *to;
    CellClass *bcptr;

    bool passed = true;

    _iobuf *file = fopen("MapCheck.txt", "w");

    Unknown_0055A550();
    from = Unknown_0055A490();
    while (from != 0) {
        if (Unknown_0055A740(from, true)) {

            for (int mzone = 0; mzone < 12; mzone++) {
                if (mzone != 9 && mzone != 6) {

                    from_ground = unknown_table_7e00c4[mzone][from->unknown_4c] == 1;

                    from_bridge = (from->unknown_140 & 0x100)
                        && (((from->unknown_140 & 0x800) && ((bcptr = from->unknown_2c) == 0 || bcptr->MapCoords.Y - from->MapCoords.Y != 2))
                            || (!(from->unknown_140 & 0x800) && ((bcptr = from->unknown_2c) == 0 || bcptr->MapCoords.X - from->MapCoords.X != 2)));

                    if (from_ground || from_bridge) {
                        unknown_118 = MapLocalSize.X + 1 + MapLocalSize.Y;
                        unknown_11c = MapLocalSize.Y - MapLocalSize.X + MapSize.Width;
                        to = Unknown_0055A910();
                        while (to != 0) {

                            if ((to->MapCoords.X + to->MapCoords.Y > from->MapCoords.X + from->MapCoords.Y) || (to->MapCoords.X + to->MapCoords.Y == from->MapCoords.X + from->MapCoords.Y && to->MapCoords.X - to->MapCoords.Y > from->MapCoords.X - from->MapCoords.Y)) {
                                to_ground = unknown_table_7e00c4[mzone][to->unknown_4c] == 1;
                                to_bridge = (to->unknown_140 & 0x100)
                                    && (((to->unknown_140 & 0x800) && ((bcptr = to->unknown_2c) == 0 || bcptr->MapCoords.Y - to->MapCoords.Y != 2))
                                        || (!(to->unknown_140 & 0x800) && ((bcptr = to->unknown_2c) == 0 || bcptr->MapCoords.X - to->MapCoords.X != 2)));

                                if (to_ground
                                    && from_ground
                                    && Unknown_0054F7C0(from->MapCoords, to->MapCoords, mzone, false, false, false)
                                    && unknown_path_estimator_8315c8.Unknown_0042AA30(from->MapCoords, to->MapCoords, 0, false, false, mzone) == 0x7FFFFFFF) {
                                    passed = false;
                                    fprintf(file, "Failure: (%d,%d)->(%d,%d) ; (ground->ground) ; MZONE %s\n", from->MapCoords.X, from->MapCoords.Y, to->MapCoords.X, to->MapCoords.Y, MovementZoneNames[mzone]);
                                }

                                if (to_bridge) {
                                    if (from_bridge
                                        && Unknown_0054F7C0(from->MapCoords, to->MapCoords, mzone, true, true, false)
                                        && unknown_path_estimator_8315c8.Unknown_0042AA30(from->MapCoords, to->MapCoords, 0, true, true, mzone) == 0x7FFFFFFF) {
                                        passed = false;
                                        fprintf(file, "Failure: (%d,%d)->(%d,%d) ; (bridge->bridge) ; MZONE %s\n", from->MapCoords.X, from->MapCoords.Y, to->MapCoords.X, to->MapCoords.Y, MovementZoneNames[mzone]);
                                    }

                                    if (from_ground
                                        && Unknown_0054F7C0(from->MapCoords, to->MapCoords, mzone, false, true, false)
                                        && unknown_path_estimator_8315c8.Unknown_0042AA30(from->MapCoords, to->MapCoords, 0, false, true, mzone) == 0x7FFFFFFF) {
                                        passed = false;
                                        fprintf(file, "Failure: (%d,%d)->(%d,%d) ; (ground->bridge) ; MZONE %s\n", from->MapCoords.X, from->MapCoords.Y, to->MapCoords.X, to->MapCoords.Y, MovementZoneNames[mzone]);
                                    }
                                }

                                if (to_ground
                                    && from_bridge
                                    && Unknown_0054F7C0(from->MapCoords, to->MapCoords, mzone, true, false, false)
                                    && unknown_path_estimator_8315c8.Unknown_0042AA30(from->MapCoords, to->MapCoords, 0, true, false, mzone) == 0x7FFFFFFF) {
                                    passed = false;
                                    fprintf(file, "Failure: (%d,%d)->(%d,%d) ; (bridge->ground) ; MZONE %s\n", from->MapCoords.X, from->MapCoords.Y, to->MapCoords.X, to->MapCoords.Y, MovementZoneNames[mzone]);
                                }
                            }

                            to = Unknown_0055A910();
                        }
                    }
                }
            }
        }

        from = Unknown_0055A490();
    }

    fclose(file);
    return passed;
}
