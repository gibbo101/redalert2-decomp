// ObjectClass clipping/draw gate existing ABI/types; diagnostic only.
#include "shared/techno.hpp"
#include "shared/tactical.hpp"
extern bool unknown_flag_a40d13;
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?Unknown_006A29D0@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
inline Rect __fastcall Intersect(Rect const &rect1, Rect const &rect2, int *x, int *y)
{
    Rect empty(0, 0, 0, 0);
    Rect result = rect2;
    if (!rect1.Is_Valid() || !rect2.Is_Valid()) {
        return empty;
    }
    if (result.X < rect1.X) {
        result.Width += result.X - rect1.X;
        result.X = rect1.X;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y < rect1.Y) {
        result.Height += result.Y - rect1.Y;
        result.Y = rect1.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (result.X + result.Width > rect1.X + rect1.Width) {
        result.Width = rect1.X - result.X + rect1.Width;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y + result.Height > rect1.Y + rect1.Height) {
        result.Height = rect1.Y + rect1.Height - result.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (x != 0) {
        *x += rect2.X - result.X;
    }
    if (y != 0) {
        *y += rect2.Y - result.Y;
    }
    return result;
}


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
