// void __fastcall Unknown_Rect_Shrink_006F1B00(Rect *rect, int amount) -- 0x006F1B00
// Shrinks a rectangle by amount on every side (hypothesis).
#include "shared/rect.hpp"

void __fastcall Unknown_Rect_Shrink_006F1B00(Rect *rect, int amount)
{
    rect->X += amount;
    rect->Y += amount;
    rect->Width -= amount * 2;
    rect->Height -= amount * 2;
}
