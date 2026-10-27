// void ParticleClass::unknown_func_6093a0() (0x006093A0)
// Behaviour 1 (gas): every other frame the drift jitters within +-5, the
// state frame advances and the speed decays.
#include "shared/particle.hpp"
#include "shared/cd_timer.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@4000c000000000000000=0079ca88

// Keeps a value within [low, high].
static inline void Limit(int &value, int low, int high)
{
    if (value < low) {
        value = low;
    } else if (value > high) {
        value = high;
    }
}

void ParticleClass::unknown_func_6093a0()
{
    if (Frame & 1) {
        if ((abs(unknown_id_source_a3d290->Random()()) & 3) == 0) {
            int dx = 0;
            int dy = 0;
            if ((abs(unknown_id_source_a3d290->Random()()) & 1) == 0) {
                dx = abs(unknown_id_source_a3d290->Random()()) % 3 - 1;
            } else {
                dy = abs(unknown_id_source_a3d290->Random()()) % 3 - 1;
            }
            unknown_b0.X += dx;
            unknown_b0.Y += dy;
            Limit(unknown_b0.X, -5, 5);
            Limit(unknown_b0.Y, -5, 5);
        }
        unknown_b0.Z = 0;
    }
    if (unknown_11e < Class->EndStateAI) {
        if ((Fetch_ID() + (Class->MaxEC - Lifetime)) % ((Fetch_ID() & 1) + Class->StateAIAdvance) == 0) {
            unknown_11e++;
        }
        if (unknown_11e == Class->EndStateAI && Class->DeleteOnStateLimit) {
            unknown_121 = true;
        }
    }
    if (Velocity > 3.0) {
        Velocity -= Class->Deacc;
    }
}
