#include "shared/particle.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/rules.hpp"
// @ref _unknown_geometry_j=00a76510
// @ref _unknown_geometry_g=00a76524
// @ref ?unknown_wind_7eb824=007eb824
static inline Point2D Wind_Offset(int const &direction, int effect) { Point2D offset; offset.X = unknown_wind_7eb824[0][direction] * effect; offset.Y = unknown_wind_7eb824[1][direction] * effect; return offset; }
void ParticleClass::unknown_func_60a230()
{
    CoordStruct next = Coord;
    CoordStruct coord = Coord;
    int effect = Class->WindEffect;
    
    Point2D offset = Wind_Offset(Rules->unknown_6d4, effect);
    next.X += offset.X; next.Y += offset.Y;
    next.Z += (int)Velocity;
    next.X += unknown_b0.X;
    next.Y += unknown_b0.Y;
    next.Z += unknown_b0.Z;
    if (Map[coord].unknown_140 & 0x100) {
        int height = Map.Unknown_0055A280(coord) + unknown_geometry_j;
        if (coord.Z < height && next.Z >= (double)height - unknown_geometry_g * 2.5) {
            unknown_121 = true;
            return;
        }
    }
    unknown_slot103(next);
}

// @ref __real@8@4000a000000000000000=007a7f38
