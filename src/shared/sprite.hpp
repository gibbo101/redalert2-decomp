// sprite.cpp (0x0068B7E0-0x0068BC4F; TibSun sprite.cpp): the scaled and rotated
// bitmap blitter and its 256-entry fixed-point sine and cosine tables.
#ifndef RA2_SHARED_SPRITE_HPP
#define RA2_SHARED_SPRITE_HPP

#include "shared/surface.hpp"

// An 8-bit bitmap in memory (TibSun sprite.cpp's file-local class).
class BitmapClass
{
public:
    BitmapClass(int w, int h, unsigned char *data) : Width(w), Height(h), Data(data) {}
    int Width;              // +0x00
    int Height;             // +0x04
    unsigned char *Data;    // +0x08
};

// Sine and cosine of an 8-bit angle in 8.8 fixed point (0x007F44C4, 0x007F48C4).
extern int _SineTab[256];
extern int _CosineTab[256];

// Draws bmp scaled (24.8 fixed point) and rotated by angle (0..255) centred
// on pt, skipping colour 0; no clipping (0x0068B800; no callers in the executable).
void __fastcall Scale_Rotate(Surface &surf, BitmapClass &bmp, Point2D const &pt, int scale, unsigned char angle);

#endif
