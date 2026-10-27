// void ParticleClass::unknown_func_60a350() (0x0060A350; inlined into
// 0x0060A420, never called)
// Movement of behaviour 2: a moving particle (Velocity > 0) steps by
// unknown_f0 and is marked done (unknown_11d, unknown_121) when the ground
// under the new position is higher than under the old one; then the
// position is set (slot 103).
#include "shared/particle.hpp"
#include "shared/map_view.hpp"
// @ref __real@8@00000000000000000000=0079b610

void ParticleClass::unknown_func_60a350()
{
    CoordStruct next = Coord;
    CoordStruct coord = Coord;
    if (Velocity > 0.0) {
        next.X += unknown_f0.X;
        next.Y += unknown_f0.Y;
        next.Z += unknown_f0.Z;
    }
    if (Velocity > 0.0) {
        int height = Map.Unknown_0055A280(coord);
        if (Map.Unknown_0055A280(next) > height) {
            unknown_11d = 1;
            unknown_121 = true;
        }
    }
    unknown_slot103(next);
}
