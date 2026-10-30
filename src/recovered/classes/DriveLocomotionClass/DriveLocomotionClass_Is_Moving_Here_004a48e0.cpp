// bool __stdcall DriveLocomotionClass::Is_Moving_Here(CoordStruct to) (0x004A48E0, ILocomotion 40)
// Whether the unit is headed for the coordinate's cell (within the height
// tolerance): the marked point ahead on its track, else the head-to coordinate.
#include "shared/drive_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ?DriveRawTracks@@3QBURawTrackStruct@@B=007a00b0
// @ref ?DriveTrackControl@@3QBUTrackControlStruct@@B=007a0180
// @ref ?Smooth_Turn@DriveLocomotionClass@@QAE?AUPoint2D@@ABU2@AAH@Z=004a4740
// @ref _unknown_geometry_g=008529d0

bool __stdcall DriveLocomotionClass::Is_Moving_Here(CoordStruct to)
{
    UnknownCoord434820 head = Head_To_Coord();
    if (head == unknown_coord_852998) {
        return false;
    }
    if (!unknown_60 && unknown_58 != -1) {
        int track = DriveTrackControl[unknown_58].Track;
        if (track) {
            TrackType const *points = DriveRawTracks[track - 1].Track;
            int cell = DriveRawTracks[track - 1].Cell;
            if (cell > -1) {
                int facing = points[cell].Facing;
                if (unknown_5c < cell) {
                    Point2D offset = points[cell].Offset;
                    Point2D point = Smooth_Turn(offset, facing);
                    CoordStruct coord(point.X, point.Y, Object_Coord(LinkedTo).Z);
                    if (Coord_Cell(coord) == Coord_Cell(to) && abs(coord.Z - to.Z) <= unknown_geometry_g) {
                        return true;
                    }
                }
            }
        }
    }
    if (Coord_Cell(head) == Coord_Cell(to) && abs(head.Z - to.Z) <= unknown_geometry_g) {
        return true;
    }
    return false;
}
