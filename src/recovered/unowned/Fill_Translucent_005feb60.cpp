// Fill a locked surface rectangle through the owner-draw alpha blend, 005FEB60.
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"
void __fastcall Unknown_005feb60(Rect *area, Surface *surface, int color, int alpha)
{
    unsigned short *pixels = (unsigned short *)surface->Lock();
    if (pixels) {
        int stride = surface->Stride() / 2;
        for (int y = area->Y; y < area->Y + area->Height; ++y) {
            int index = y * stride + area->X;
            for (int x = area->X; x < area->X + area->Width; ++x) {
                pixels[index] = OwnerDraw::Blend_Color(pixels[index], color, alpha);
                ++index;
            }
        }
        surface->Unlock();
    }
}
