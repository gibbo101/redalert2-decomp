// void MapClass::Unknown_00563D40() (0x00563D40)
// Rebuilds the subzone tracking: each of the three vectors, from the last,
// is cleared and refilled by 0x00563D80; then the path estimator is reset.
#include "shared/map.hpp"
#include "shared/path_estimator.hpp"
// @ref ?Unknown_00563D80@MapClass@@QAEXH@Z=00563d80
// @ref ?unknown_path_estimator_8315c8@@3UUnknownPathEstimator@@A=008315c8
// @ref ?Unknown_00429A90@UnknownPathEstimator@@QAEXXZ=00429a90

void MapClass::Unknown_00563D40()
{
    for (int index = 2; index >= 0; index--) {
        SubzoneTracking[index].Clear();
        Unknown_00563D80(index);
    }
    unknown_path_estimator_8315c8.Unknown_00429A90();
}
