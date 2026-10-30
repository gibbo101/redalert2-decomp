// CoordStruct Tactical::Unknown_006A2BF0(Point2D const &point) (0x006A2BF0): a point inside the
// screen rectangle 0x00ABE560 run through the projection +0xDE4 to a ground coordinate; otherwise
// the unit's empty coordinate (header static unknown_geometry_l).
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_rect_abe560@@3VRect@@A=00abe560
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

CoordStruct Tactical::Unknown_006A2BF0(Point2D const &point)
{
    int x = point.X;
    if (x < unknown_rect_abe560.Width) {
        int y = point.Y;
        if (y < unknown_rect_abe560.Height) {
            Vector3 position;
            position.X = (float)x;
            position.Y = (float)y;
            position.Z = 0.0f;
            position = unknown_de4 * position;
            return CoordStruct((int)position.X, (int)position.Y, 0);
        }
    }
    return unknown_geometry_l;
}
