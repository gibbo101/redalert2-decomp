// void __fastcall unknown_clear_rect(RectangleStruct const &rect) -- 0x00717C80
// Purpose: zeroes the inclusive rectangle rect (X..X+Width, Y..Y+Height) of
// the 256-byte-wide byte map at 0x00AD0A70.
// Assumptions: the map's owner and height are unknown.
// @ref ?unknown_byte_map_ad0a70@@3PAY0BAA@EA=00ad0a70
#include "shared/crt_string.hpp"

struct RectangleStruct {
    int X;
    int Y;
    int Width;
    int Height;
};

extern unsigned char unknown_byte_map_ad0a70[][256];

void __fastcall unknown_clear_rect(RectangleStruct const &rect)
{
    for (int y = rect.Y; y <= rect.Y + rect.Height; y++) {
        memset(&unknown_byte_map_ad0a70[y][rect.X], 0, rect.Width + 1);
    }
}
