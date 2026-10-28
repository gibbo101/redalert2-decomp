// void DriveLocomotionClass::unknown_4a0bc0(CoordStruct const &headto, int mark) (0x004A0BC0)
// Marks (slot 58) or clears (slot 59, mark 0) the cell ahead on the current
// track and the head-to coordinate (Westwood's DriveClass::Mark_Track).
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ?DriveRawTracks@@3QBURawTrackStruct@@B=007a00b0
// @ref ?DriveTrackControl@@3QBUTrackControlStruct@@B=007a0180

void DriveLocomotionClass::unknown_4a0bc0(CoordStruct const &headto, int mark)
{
    if (headto == unknown_coord_852998) {
        return;
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
                    if (mark == 0) {
                        CoordStruct coord(point.X, point.Y, LinkedTo->unknown_slot110());
                        LinkedTo->unknown_slot59(coord);
                    } else if (mark == 1 || mark == 3) {
                        CoordStruct coord(point.X, point.Y, LinkedTo->unknown_slot110());
                        LinkedTo->unknown_slot58(coord);
                    }
                }
            }
        }
    }
    if (mark == 0) {
        LinkedTo->unknown_slot59(headto);
    } else if (mark == 1 || mark == 3) {
        LinkedTo->unknown_slot58(headto);
    }
}
