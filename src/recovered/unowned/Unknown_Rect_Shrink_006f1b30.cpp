// void __fastcall Unknown_Rect_Shrink_006F1B30(Rect *rect, int x, int y) -- 0x006F1B30
// Shrinks a rectangle by x on the left and right and by y on the top and bottom (hypothesis).
#include "shared/rect.hpp"

void __fastcall Unknown_Rect_Shrink_006F1B30(Rect *rect, int x, int y)
{
    rect->X += x;
    rect->Y += y;
    rect->Width -= x * 2;
    rect->Height -= y * 2;
}
