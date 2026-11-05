// @ref ??0Vector3@@QAE@MMM@Z=00437690
// Point2D Tactical::Unknown_006A2900(Point2D const &) (0x006A2900): a screen
// point run through the projection matrix at +0xDE4 (the techno types' smoke
// offsets use it).
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

Point2D Tactical::Unknown_006A2900(Point2D const &point)
{
    Vector3 position((float)point.X,(float)point.Y,0.0f);
    position = unknown_de4 * position;
    return Point2D((int)position.X, (int)position.Y);
}
