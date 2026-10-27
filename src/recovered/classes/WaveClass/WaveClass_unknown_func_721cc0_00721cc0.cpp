// void WaveClass::unknown_func_721cc0() (0x00721CC0)
// The offsets of the eight neighbours of a pixel on the current surface
// (rows are Stride / 2 pixels), and the offset of the wave's direction
// repeated once, twice and three times.
#include "shared/wave.hpp"
#include "shared/surface.hpp"
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c

void WaveClass::unknown_func_721cc0()
{
    int row = unknown_surface_83995c->Stride() >> 1;
    unknown_174[0] = -row;
    unknown_174[1] = 1 - row;
    unknown_174[2] = 1;
    unknown_174[3] = row + 1;
    unknown_174[4] = row;
    unknown_174[5] = row - 1;
    unknown_174[6] = -1;
    unknown_174[7] = -1 - row;
    PixelOffsets_1d0[0] = 0;
    PixelOffsets_1d0[1] = 0;
    int *step = &unknown_174[unknown_194];
    PixelOffsets_1d0[2] = *step;
    PixelOffsets_1d0[3] = *step;
    PixelOffsets_1d0[4] = *step;
    PixelOffsets_1d0[5] = *step;
    PixelOffsets_1d0[6] = *step;
    PixelOffsets_1d0[7] = *step << 1;
    PixelOffsets_1d0[8] = *step << 1;
    PixelOffsets_1d0[9] = *step << 1;
    PixelOffsets_1d0[10] = *step * 3;
    PixelOffsets_1d0[11] = *step * 3;
    PixelOffsets_1d0[12] = *step * 3;
}
