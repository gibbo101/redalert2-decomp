// Whether a waypoint is in range and set (0x00663240).
bool UnknownIDSource::Unknown_00663240(int waypoint) const
{
    if (waypoint < 101 && waypoint >= 0 && Waypoints[waypoint] != unknown_geometry_k) {
        return true;
    }
    return false;
}
