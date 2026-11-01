// void RadarEventClass::Get_Event_Rect(Point2D (&event_rect)[4]) const -- 0x0063C270 (TS revent.cpp)
// The four corners of the event's square: the radius rotated by the rotation angle, then turned by
// quarter turns.
#include "shared/radar_event_class.hpp"
#include "shared/matrix3d.hpp"
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

void RadarEventClass::Get_Event_Rect(Point2D (&event_rect)[4]) const
{
    Matrix3D matrix;
    matrix.Make_Identity();
    matrix.Rotate_Z(RotationAngle);
    Vector3 vector(Radius, 0, 0);
    vector = matrix * vector;
    int x_radius = vector.X;
    int y_radius = vector.Y;
    event_rect[0] = Point2D(x_radius, y_radius);
    event_rect[1] = Point2D(-y_radius, x_radius);
    event_rect[2] = Point2D(-x_radius, -y_radius);
    event_rect[3] = Point2D(y_radius, -x_radius);
}
