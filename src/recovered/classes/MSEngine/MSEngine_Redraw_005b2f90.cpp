// void MSEngine::Redraw() (0x005B2F90)
// Forces a full repaint of the hidden surface.
#include "shared/ms_engine.hpp"
#include "shared/dsurface.hpp"
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref ?Draw@MSEngine@@QAEXPAVSurface@@@Z=005b2fb0

void MSEngine::Redraw()
{
    unknown_redraw_8523dc = true;
    Draw(unknown_surface_839954);
}
