#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Inflate(Rect &rect, int amount) (0x00612570)
#include "shared/planning.hpp"

void __fastcall Planning_Inflate(Rect &rect, int amount)
{
    int twice = amount * 2;
    if (twice < 0 && (twice >= rect.Width || twice >= rect.Height)) {
        rect.X = 0;
        rect.Y = 0;
        rect.Width = 0;
        rect.Height = 0;
        return;
    }
    rect.X -= amount;
    rect.Y -= amount;
    rect.Width += twice;
    rect.Height += twice;
}
