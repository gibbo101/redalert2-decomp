// void ShipLocomotionClass::unknown_676b20(CoordStruct const &headto, int mark) (0x00676B20)
// Marks (slot 58) or clears (slot 59, mark 0) the cell ahead on the current
// track and the head-to coordinate (Westwood's DriveClass::Mark_Track).
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?ShipRawTracks@@3QBURawTrackStruct@@B=007aad20
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0

void ShipLocomotionClass::unknown_676b20(CoordStruct const &headto, int mark)
{
    if (headto == unknown_coord_ab91c8) {
        return;
    }
    if (!unknown_60 && unknown_58 != -1) {
        int track = ShipTrackControl[unknown_58].Track;
        if (track) {
            TrackType const *points = ShipRawTracks[track - 1].Track;
            int cell = ShipRawTracks[track - 1].Cell;
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
