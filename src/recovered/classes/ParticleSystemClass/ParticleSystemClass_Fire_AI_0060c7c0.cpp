// @ref __real@4@4000c000000000000000=007a815c
// @ref __real@4@4006c800000000000000=007a8160
// Fire particles track a rotating source and oscillate around its target.
#include "shared/unknown_vector3.hpp"
#include "shared/particle_system.hpp"
#include "shared/techno.hpp"
#include "shared/fast_math.hpp"
#include "shared/rect.hpp"
extern "C" void * __cdecl memcpy(void *, void const *, unsigned int);
extern short Wave_Sine_Table_00af91e4[500];
extern int Particle_Fire_Step_X[8];
extern int Particle_Fire_Step_Y[8];
int __fastcall Wave_Direction_00721db0(Point2D const &start, Point2D const &end);
// @ref ?Wave_Sine_Table_00af91e4@@3PAFA=00af91e4
// @ref ?Particle_Fire_Step_X@@3PAHA=007eb884
// @ref ?Particle_Fire_Step_Y@@3PAHA=007eb8a4
// @ref ?Wave_Direction_00721db0@@YIHABUPoint2D@@0@Z=00721db0
inline CoordStruct Particle_Coord_Along_Facing(UnknownFacingDir facing, int distance, CoordStruct coord)
{
    double angle = ((short)facing.Raw - 16383) * -9.587672516830327e-05;
    int z = coord.Z;
    int y = (int)(coord.Y - (double)Fast_Sin(angle) * distance);
    int x = (int)(coord.X + (double)Fast_Cos(angle) * distance);
    UnknownVector3 point(x, y, z);
    CoordStruct result;
    memcpy(&result, &point, sizeof result);
    return result;
}
void ParticleSystemClass::unknown_func_60c7c0()
{
    int i;
    for (i = Particles.Count() - 1; i >= 0; --i) {
        ParticleClass *particle = Particles[i];
        particle->unknown_func_609c90();
        particle->unknown_func_60a420();
    }
    for (i = Particles.Count() - 1; i >= 0; --i) {
        ParticleClass *particle = Particles[i];
        if (particle->unknown_121) particle->unknown_slot60();
    }
    bool reaimed = false;
    TechnoClass *source = Owner->As_Techno();
    if (source) {
        if (source->unknown_7d) {
            if (source->unknown_228 && source->unknown_2e0.Is_Rotating()) {
                CoordStruct target = source->unknown_228->Center_Coord();
                CoordStruct delta = target - source->Position_Coord_004f3f40();
                int distance = (int)Fast_Sqrt((double)delta.X * delta.X + (double)delta.Y * delta.Y + (double)delta.Z * delta.Z);
                TargetCoord = Particle_Coord_Along_Facing(source->unknown_2e0.Current(), distance, source->Position_Coord_004f3f40());
                unknown_slot103(source->unknown_slot43(0));
                reaimed = true;
            }
        }
        if (!source->unknown_7d) unknown_slot60();
    } else unknown_slot60();
    if (!unknown_e4 && (!(Frame % Class->SpawnFrames) || (!(Frame % 3) && reaimed))) {
        int index = Frame % 500;
        CoordStruct delta = Position_Coord_004f3f40() - TargetCoord;
        int squared = delta.X * delta.X + delta.Y * delta.Y + delta.Z * delta.Z;
        int divisor;
        if ((float)Fast_Sqrt((double)squared) < 200.0f) divisor = 3;
        else divisor = 1;
        int offset = (int)((double)(12 * Wave_Sine_Table_00af91e4[index]) / ((float)divisor * 3.0f));
        Point2D to(TargetCoord.X, TargetCoord.Y);
        CoordStruct position = Position_Coord_004f3f40();
        int facing = Wave_Direction_00721db0(Point2D(position.X, position.Y), to);
        CoordStruct spread = CoordStruct(Particle_Fire_Step_X[facing] * offset, Particle_Fire_Step_Y[facing] * offset, 0);
        Spawn_Particle(Position_Coord_004f3f40() + CoordStruct(0, 0, 1), TargetCoord + spread, 4);
    }
}
