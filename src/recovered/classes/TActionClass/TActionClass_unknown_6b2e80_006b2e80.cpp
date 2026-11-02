// CoordStruct TActionClass::unknown_6b2e80() const (0x006B2E80)
// The coordinate of the waypoint Data.Value (UnknownIDSource 0x006631C0).
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
// @ref ?Waypoint_Coord@UnknownIDSource@@QBE?AUCoordStruct@@H@Z=006631c0

CoordStruct TActionClass::unknown_6b2e80() const
{
    return unknown_id_source_a3d290->Waypoint_Coord(Data.Value);
}


