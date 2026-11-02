// CoordStruct Tactical::Unknown_006A2B10(Point2D const &point) (0x006A2B10): the
// coordinate under a screen point: the point plus the view position through the
// projection matrix at +0xDE4, Z 0; the unit's zero coordinate when the point
// lies right of or below the rectangle at 0x00ABE560 (hypothesis).
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_rect_abe560@@3VRect@@A=00abe560
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

CoordStruct Tactical::Unknown_006A2B10(Point2D const &point)
{
    if (point.X < unknown_rect_abe560.Width && point.Y < unknown_rect_abe560.Height + unknown_rect_abe560.Y) {
        Point2D view(TacPixelX, TacPixelY);
        Point2D pixel(point.X + view.X, point.Y + view.Y);
        Vector3 position;
        position.X = (float)pixel.X;
        position.Y = (float)pixel.Y;
        position.Z = 0.0f;
        position = unknown_de4 * position;
        return CoordStruct((int)position.X, (int)position.Y, 0);
    }
    return unknown_geometry_l;
}
