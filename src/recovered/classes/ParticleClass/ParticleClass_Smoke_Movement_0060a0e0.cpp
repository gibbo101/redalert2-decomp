#include "shared/particle.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/rules.hpp"
#include "shared/cd_timer.hpp"
// @ref ?unknown_wind_7eb7e4=007eb7e4
static inline Point2D Smoke_Wind_Offset(int const &direction) { Point2D offset; offset.X = unknown_wind_7eb7e4[0][direction]; offset.Y = unknown_wind_7eb7e4[1][direction]; return offset; }
#define MIN(a,b) (((b)<(a))?(b):(a))
void ParticleClass::unknown_func_60a0e0()
{
    int frame = Frame;
    CoordStruct next = Coord;
    if (Class->WindEffect > 0 && frame % (10 / Class->WindEffect) == 0) {
        Point2D offset = Smoke_Wind_Offset(Rules->unknown_6d4);
        next.X += offset.X; next.Y += offset.Y;
    }
    if (frame & 1) {
        next.X = (int)(next.X + unknown_bc);
        next.Y = (int)(next.Y + unknown_c0);
        int height = Map.Unknown_0055A280(next);
        if (next.Z > height + 5) {
            next.Z -= MIN(2, next.Z - height - 5);
        }
        next.X += unknown_b0.X;
        next.Y += unknown_b0.Y;
        next.Z += unknown_b0.Z;
        if (next.Z < Map.Unknown_0055A280(next) + 5) next.Z = Map.Unknown_0055A280(next) + 5;
    }
    unknown_slot103(next);
}
