// Polygon input and scanline storage shared by Polygon.cpp and WaveClass.
#ifndef RA2_SHARED_WAVE_GEOMETRY_HPP
#define RA2_SHARED_WAVE_GEOMETRY_HPP
#include "shared/rect.hpp"
class NoInitClass;

// Two real embedded geometry states: 61BE40 receives ECX=input, EDX=scanlines.
// Names are behavioral hypotheses; no RTTI for these nonvirtual objects.
struct WavePolygonInput {
    WavePolygonInput() : Count(0), Points(0) {}
    WavePolygonInput(NoInitClass const &) : Points(0) {}
    int Count;
    Point2D *Points;
    // Six independently constructed geometry points; their observed contiguous layout is unchanged.
    Point2D InlinePoint0;
    Point2D InlinePoint1;
    Point2D InlinePoint2;
    Point2D InlinePoint3;
    Point2D InlinePoint4;
    Point2D InlinePoint5;
};
struct WaveScanlineBuffer {
    WaveScanlineBuffer() : Count(0), FirstY(0), Spans(0) {}
    WaveScanlineBuffer(NoInitClass const &) : Spans(0) {}
    int Count;
    int FirstY;
    Point2D *Spans;
};
typedef char WavePolygonInput_size[(sizeof(WavePolygonInput) == 0x38) ? 1 : -1];
typedef char WaveScanlineBuffer_size[(sizeof(WaveScanlineBuffer) == 0x0C) ? 1 : -1];

#endif
