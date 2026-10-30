// UnknownPathEstimator::Unknown_0042AA30() (0x0042AA30): the estimated
// length of a walk between two cells (Tiberian Sun's Test_Cell_Walk;
// hypothesis).
// @ref _unknown_geometry_k=0084e7a8
// @ref ?Unknown_00429B60@UnknownPathEstimator@@QAE_NABVCell@@0HPAVFootClass@@@Z=00429b60
// @ref ?Unknown_00564F70@MapClass@@QAE?AVCell@@PAVCellClass@@_N@Z=00564f70
// @ref ?Unknown_00565610@MapClass@@QAE?AVCell@@ABV2@HI@Z=00565610
#include "shared/path_estimator.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/crt_memory.hpp"

template <class T> T max(T a, T b)
{
    return a > b ? a : b;
}

int UnknownPathEstimator::Unknown_0042AA30(Cell const &from, Cell const &to, FootClass *foot, bool from_bridge, bool to_bridge, int arg6)
{
    unknown_38 = true;
    Unknown_00427E90();
    for (int index = 0; index < 3; index++) {
        unknown_74[index].Clear();
    }
    CellClass *from_ptr = &Map[from];
    CellClass *to_ptr = &Map[to];
    Cell hs_from = Map.Unknown_00564F70(from_ptr, from_bridge);
    Cell hs_to = Map.Unknown_00564F70(to_ptr, to_bridge);
    if (arg6 == -1) {
        if (foot) {
            arg6 = foot->unknown_slot32()->MovementZone;
        } else {
            arg6 = 0;
        }
    }
    if (Unknown_00429B60(hs_from, hs_to, arg6, foot)) {
        int radius = max(abs(from.X - to.X), abs(from.Y - to.Y));
        int node_count = unknown_c74[0];
        int distance = 2 * node_count - 2;
        bool add_bridge_dist = true;
        if (to_bridge && from_bridge) {
            int to_conn = Map.Unknown_005500D0(to, 3, 0);
            int from_conn = Map.Unknown_005500D0(from, 3, 0);
            if (to_conn == from_conn && to_conn != -1) {
                add_bridge_dist = false;
            }
        }
        if (add_bridge_dist) {
            if (to_bridge) {
                Cell bridge_end = unknown_geometry_k;
                if (node_count >= 4) {
                    bridge_end = Map.Unknown_00565610(to, 0, unknown_bc[0][node_count - 2]);
                }
                if (node_count < 4 || bridge_end == unknown_geometry_k) {
                    bridge_end = Map.Unknown_00565610(to, 0, unknown_bc[0][node_count - 1]);
                }
                if (bridge_end == unknown_geometry_k) {
                    bridge_end = hs_to;
                }
                if (bridge_end != unknown_geometry_k) {
                    distance += max(abs(to.X - bridge_end.X), abs(to.Y - bridge_end.Y));
                }
            }
            if (from_bridge) {
                Cell bridge_end = unknown_geometry_k;
                if (node_count >= 4) {
                    bridge_end = Map.Unknown_00565610(from, 0, unknown_bc[0][1]);
                }
                if (node_count < 4 || bridge_end == unknown_geometry_k) {
                    bridge_end = Map.Unknown_00565610(from, 0, unknown_bc[0][0]);
                }
                if (bridge_end == unknown_geometry_k) {
                    bridge_end = hs_from;
                }
                if (bridge_end != unknown_geometry_k) {
                    distance += max(abs(from.X - bridge_end.X), abs(from.Y - bridge_end.Y));
                }
            }
            if (distance > radius) {
                return distance;
            }
        }
        return radius;
    }
    return 0x7FFFFFFF;
}
