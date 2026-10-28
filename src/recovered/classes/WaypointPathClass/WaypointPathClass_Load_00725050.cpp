// HRESULT __stdcall WaypointPathClass::Load(IStream *stream) (0x00725050):
// restores the path in place, rebuilds the waypoint list and reads the
// waypoints back (a count and 12-byte records).
#include "shared/waypoint_path.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??0?$VectorClass@UWaypointClass@@@@QAE@IPBUWaypointClass@@@Z=00725b40

HRESULT __stdcall WaypointPathClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) WaypointPathClass(NoInitClass());
    int count;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    new (&Waypoints) DynamicVectorClass<WaypointClass>;
    for (int index = 0; index < count; index++) {
        WaypointClass waypoint;
        result = stream->Read(&waypoint, sizeof(waypoint), 0);
        if (FAILED(result)) {
            return result;
        }
        Waypoints.Add(waypoint);
    }
    return S_OK;
}
