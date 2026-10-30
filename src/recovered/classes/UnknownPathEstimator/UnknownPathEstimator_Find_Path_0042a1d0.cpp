// Hierarchical corridor selection and regular-search retries, 0x0042A1D0.
#define COM_PTR_IMPLEMENT_RELEASE
#include "shared/infantry.hpp"
#include "shared/path_estimator.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Find_Path_Regular_00427370@UnknownPathEstimator@@QAEPAUUnknownPathType@@ABVCell@@0PAVFootClass@@PAHH_N@Z=00427370
// @ref _unknown_path_hierarchical_failure=007cf1d0
// @ref _unknown_path_regular_failure=007cf170
// @ref _unknown_path_without_hs=007cf1a0
extern "C" char unknown_path_hierarchical_failure[];
extern "C" char unknown_path_regular_failure[];
extern "C" char unknown_path_without_hs[];

UnknownPathType *UnknownPathEstimator::Find_Path_0042a1d0(Cell const &from, Cell const &to, FootClass *foot, int *moves, int max_loops, int zone, int avoidance)
{
    unknown_38 = true;
    Unknown_00427E90();
    for (int i = 0; i < 3; ++i) {
        unknown_74[i].Clear();
    }
    unknown_3c = avoidance;
    CellClass *from_cell = &Map[from];
    CellClass *to_cell = &Map[to];
    int from_zone = Map.Zone(from, zone != -1 ? zone : foot->unknown_slot32()->MovementZone, foot->unknown_79);
    int to_zone = Map.Zone(to, zone != -1 ? zone : foot->unknown_slot32()->MovementZone, (Map[to].unknown_140 & 0x100) != 0);
    Cell hs_from = Map.Unknown_00564F70(from_cell, foot->unknown_79);
    Cell hs_to = Map.Unknown_00564F70(to_cell, (to_cell->unknown_140 & 0x100) != 0);
    int move_zone = zone != -1 ? zone : foot->unknown_slot32()->MovementZone;
    if (foot->Kind_Of() == 15 && ((InfantryClass *)foot)->Type->JumpJet) {
        move_zone = 7;
        UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist((ILocomotion *)foot->Locomotor);
        GUID id;
        persist.Checked()->GetClassID(&id);
    }
    bool with_hs;
    if (foot->unknown_slot32()->IsTrain) {
        with_hs = false;
    } else if (!foot->unknown_32d || foot->unknown_slot189()) {
        with_hs = false;
    } else if (!Map.Unknown_0055A660(hs_from, true) || !Map.Unknown_0055A660(hs_to, true)) {
        with_hs = false;
    } else {
        with_hs = true;
    }
    if (from_zone != to_zone) {
        if (with_hs) {
            return 0;
        }
    }
    if (with_hs) {
        if (!Unknown_00429B60(hs_from, hs_to, move_zone, foot)) {
            Debug_Printf(unknown_path_hierarchical_failure, hs_from.X, hs_from.Y, hs_to.X, hs_to.Y);
            with_hs = false;
        }
    }
    UnknownPathType *path = 0;
    int attempt = 0;
    int tries = max_loops == -1 ? 5 : 1;
    while (true) {
        if (!with_hs) {
            Debug_Printf(unknown_path_without_hs, hs_from.X, hs_from.Y, hs_to.X, hs_to.Y);
        }
        path = Find_Path_Regular_00427370(from, to, foot, moves, max_loops, with_hs);
        if (path || !with_hs) {
            break;
        }
        int dy = abs(from.Y - to.Y);
        int dx = abs(from.X - to.X);
        if (dx <= dy) {
            dx = dy;
        }
        if (dx > 1) {
            Debug_Printf(unknown_path_regular_failure, hs_from.X, hs_from.Y, hs_to.X, hs_to.Y);
        }
        ++attempt;
        Unknown_0042A590((int)foot);
        Unknown_00427E90();
        with_hs = unknown_38 ? true : false;
        if (attempt >= tries) {
            break;
        }
        if (with_hs && !Unknown_00429B60(hs_from, hs_to, move_zone, foot)) {
            break;
        }
    }
    return path;
}
