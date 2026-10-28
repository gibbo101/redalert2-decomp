// The name of the first waypoint that is not set ("" when all are;
// 0x00663440).
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/ccini_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/waypoint_string.hpp"
#include "shared/unknown_geometry.hpp"

char const *UnknownIDSource::Free_Waypoint_Name() const
{
    for (int index = 0; index < 101; index++) {
        if (!Unknown_00663240(index)) {
            return Waypoint_As_String(index);
        }
    }
    return unknown_string_83c55c;
}
