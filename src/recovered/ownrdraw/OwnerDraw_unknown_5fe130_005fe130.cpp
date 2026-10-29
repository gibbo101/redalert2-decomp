// @ref __real@4@3ffb8000000000000000=007a7b20
// @ref __real@4@3ffe99999a0000000000=007a7b1c
// @ref __real@4@3ffdcccccd0000000000=007a7b18
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// A brightness factor for a palette index: 1.0, or 0.4..1.0 within 16 of 0x2B, 0x80 or 0xD5 (0x005FE130).
float __fastcall unknown_5fe130(int value)
{
    int centers[3] = { 0x2b, 0x80, 0xd5 };
    float factor = 1.0f;
    for (int i = 0; i < 3; i++) {
        int center = centers[i];
        if (value > center - 16 && value <= center) {
            factor = 0.6f * ((center - value) * 0.0625f) + 0.4f;
        } else if (value > center && value <= center + 16) {
            factor = 0.6f * ((value - center) * 0.0625f) + 0.4f;
        }
    }
    return factor;
}

}
