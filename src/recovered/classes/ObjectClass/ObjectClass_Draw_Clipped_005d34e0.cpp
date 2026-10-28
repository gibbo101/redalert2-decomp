// ObjectClass clipping/draw gate existing ABI/types; diagnostic only.
#include "shared/techno.hpp"
#include "shared/tactical.hpp"
extern bool unknown_flag_a40d13;
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?Unknown_006A29D0@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
#include "shared/rect_intersect.hpp"

bool ObjectClass::unknown_slot63(Rect *bounds, bool redraw, bool arg3)
{
    Point2D pixel;
    if (!unknown_flag_a40d13 && unknown_b263d8 && ((!redraw && !unknown_75) || unknown_76)) goto not_drawable;
    unknown_75 = false;
    if (unknown_tactical_83996c->Unknown_006A29D0(unknown_slot42(), pixel) || Kind_Of() == 24)
        goto draw_clipped;
not_drawable:
    return false;
draw_clipped:
    *bounds = bounds->Intersect(unknown_rect_839630);
    if (bounds->X > unknown_rect_839630.X)
        pixel.X = (int)((unsigned)pixel.X + (unsigned)unknown_rect_839630.X - (unsigned)bounds->X);
    if (bounds->Y > unknown_rect_839630.Y)
        pixel.Y = (int)((unsigned)pixel.Y + (unsigned)unknown_rect_839630.Y - (unsigned)bounds->Y);
    unknown_slot67((int)&pixel, (int)bounds);
    return true;
}
