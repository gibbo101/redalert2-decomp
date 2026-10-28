// Point2D ShipLocomotionClass::Smooth_Turn(Point2D const &offset, int &facing) (0x0067A690)
// A track point and facing turned by the current track's flags (swap,
// mirror X, mirror Y), the point placed relative to the head-to coordinate
// (Westwood's DriveClass::Smooth_Turn).
#include "shared/ship_locomotion.hpp"
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0

Point2D ShipLocomotionClass::Smooth_Turn(Point2D const &offset, int &facing)
{
    int workdir = facing;
    int flags = ShipTrackControl[unknown_58].Flag;
    int x = offset.X;
    int y = offset.Y;
    if (flags & 1) {
        int temp = x;
        x = y;
        y = temp;
        workdir = (-64 - workdir) & 0xFF;
    }
    if (flags & 2) {
        x = -x;
        workdir = -workdir & 0xFF;
    }
    if (flags & 4) {
        y = -y;
        workdir = (-128 - workdir) & 0xFF;
    }
    facing = workdir;
    return Point2D(unknown_40.X + x, unknown_40.Y + y);
}
