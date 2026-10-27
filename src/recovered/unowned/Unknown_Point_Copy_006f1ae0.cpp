// Point2D __fastcall Unknown_Point_Copy_006F1AE0(Point2D const *source) -- 0x006F1AE0
// Returns a copy of a point (hypothesis; an out-of-line Point2D copy).
#include "shared/rect.hpp"

Point2D __fastcall Unknown_Point_Copy_006F1AE0(Point2D const *source)
{
    Point2D result(source->X, source->Y);
    return result;
}
