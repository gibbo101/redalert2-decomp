// bool Tactical::Blit_Tiles() (0x006A6570): copies the tactical area of the tile
// surface (0x00839944) onto the drawing surface (0x0083995C) (TibSun
// Tactical::Blit_Tiles).
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/display.hpp"

bool Tactical::Blit_Tiles()
{
    return unknown_surface_83995c->Copy_From(unknown_rect_839630, *unknown_surface_839944, unknown_rect_839630, false, true);
}
