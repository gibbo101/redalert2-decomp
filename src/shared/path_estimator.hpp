// The path estimator at 0x008315C8 (moved out of shared/foot.hpp so the map
// units can use it without the FootClass layout).
#ifndef RA2_SHARED_PATH_ESTIMATOR_HPP
#define RA2_SHARED_PATH_ESTIMATOR_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"

class FootClass;

struct UnknownPathEstimator {
    // The length of a path between two cells for a unit (0x0042AA30; hypothesis).
    int Unknown_0042AA30(Cell const &from, Cell const &to, FootClass *foot, bool from_bridge, bool to_bridge, int arg6);
    // Resets the estimator (0x00429A90; MapClass 0x00563D40 after rebuilding the subzones).
    void Unknown_00429A90();
    // Sizes the estimator for the map rectangle (0x004284E0; MapClass 0x005499C0).
    void Unknown_004284E0(Rect const &size);
};
extern UnknownPathEstimator unknown_path_estimator_8315c8;     // 0x008315C8

#endif
