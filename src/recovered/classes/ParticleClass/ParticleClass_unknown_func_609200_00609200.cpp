#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/particle.hpp"
// Original immutable double at0x007A10F8: independently decoded value0.05.
extern "C" double const Particle_Color_Step_007a10f8;
// @ref _Particle_Color_Step_007a10f8=007a10f8
static inline void Advance_Particle_Position(Vector3 &position, Vector3 const &step) { position.X = step.X + position.X; position.Y = step.Y + position.Y; position.Z = step.Z + position.Z; }
void ParticleClass::unknown_func_609200()
{
    Vector3 direction(unknown_fc.X, unknown_fc.Y, unknown_fc.Z);
    float speed = Velocity;
    Vector3 step; step.X = direction.X * speed; step.Y = direction.Y * speed; step.Z = direction.Z * speed;
    Velocity += (unknown_id_source_a3d290->Random()(0, 0x7ffffffe) * 4.656612877414201e-10 - 0.5) * 0.1;
    Advance_Particle_Position(unknown_108, step);
    CoordStruct coord; coord.X = (int)unknown_108.X; coord.Y = (int)unknown_108.Y; coord.Z = (int)unknown_108.Z;
    unknown_slot103(coord);
    double color_change = unknown_id_source_a3d290->Random()(0, 0x7ffffffe) * 4.656612877414201e-10;
    color_change *= Particle_Color_Step_007a10f8;
    color_change += Class->ColorSpeed;
    ColorState.Fraction = color_change + ColorState.Fraction;
    if (ColorState.Fraction > 1.0) {
        if (ColorState.ColorIndex < Class->ColorList.Count() - 2) {
            ++ColorState.ColorIndex;
            ColorState.Fraction = 0;
            return;
        }
        ColorState.Fraction = 1.0;
    }
}
