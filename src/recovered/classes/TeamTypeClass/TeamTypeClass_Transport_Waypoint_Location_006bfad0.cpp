// Cell TeamTypeClass::Transport_Waypoint_Location() const (0x006BFAD0)
// The cell of the team's transport waypoint; the "no cell" value without one.
#include "shared/team_type.hpp"
#include "shared/coord.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_cell_ac00c8@@3VCell@@A=00ac00c8

// The "no cell" position (0x00AC00C8; hypothesis).
extern Cell unknown_cell_ac00c8;

Cell TeamTypeClass::Transport_Waypoint_Location() const
{
    if (TransportWaypoint == -1) {
        return unknown_cell_ac00c8;
    }
    return unknown_id_source_a3d290->Get_Waypoint_Location(TransportWaypoint);
}
