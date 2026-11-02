// HRESULT __stdcall WaypointPathClass::Save(IStream *stream, BOOL clear_dirty) (0x00725170)
// Writes the waypoint count and then each waypoint (12 bytes); TibSun waypoint.cpp shape (index
// declared first, early return when the count write fails).
#include "shared/waypoint_path.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall WaypointPathClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        int index;

        int count = Waypoints.Count();
        result = stream->Write(&count, sizeof(count), 0);
        if (FAILED(result)) {
            return result;
        }

        for (index = 0; index < count; index++) {
            result = stream->Write(&Waypoints[index], sizeof(Waypoints[index]), 0);
            if (FAILED(result)) {
                return result;
            }
        }

        result = S_OK;
    }
    return result;
}
