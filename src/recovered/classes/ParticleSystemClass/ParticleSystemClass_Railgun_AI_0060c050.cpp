// void ParticleSystemClass::unknown_func_60c050() (0x0060C050)
// Behaviour 4 (railgun): once, lays a spiral of particles along the line
// from the system to its target (with random position, direction and speed
// perturbation) and draws the laser when the type has one; then runs and
// retires the particles.
#include "shared/particle_system.hpp"
#include "shared/matrix3d.hpp"
#include "shared/fast_math.hpp"
#include "shared/laser_draw.hpp"
double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0
CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t);   // 0x007220C0
// @ref ??0ParticleClass@@QAE@PAVParticleTypeClass@@ABUCoordStruct@@1PAVParticleSystemClass@@@Z=00608440
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_func_609c90@ParticleClass@@QAEXXZ=00609c90
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Fast_Acos@@YAMN@Z=004ba550
// @ref ?Fast_Asin@@YAMN@Z=004ba580
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ?Rotate_X@Matrix3D@@QAEXM@Z=00590760
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?Lerp@@YI?AUCoordStruct@@ABU1@0M@Z=007220c0
// @ref ??0LaserDrawClass@@QAE@UCoordStruct@@0H_NVRGBClass@@22H11MM@Z=00533110
// @ref ?Add@?$DynamicVectorClass@PAVParticleClass@@@@QAE_NABQAVParticleClass@@@Z=0060d050
// @ref __real@8@3fe08000000000000000=0079c280
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@00000000000000000000=0079b610
// @ref __ftol=0077f110

static inline Vector3 Normalize(Vector3 const &v)
{
    double length = Fast_Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    if (length != 0.0) {
        return Vector3((float)(v.X / length), (float)(v.Y / length), (float)(v.Z / length));
    }
    return v;
}

static inline Vector3 &operator+=(Vector3 &a, Vector3 const &b)
{
    a.X += b.X;
    a.Y += b.Y;
    a.Z += b.Z;
    return a;
}

// The limit is only ever compared as a value: read through this inline, VC6
// loads it before the compare (fld; fcompp) instead of folding it into fcomp.
static inline double Velocity_Limit(ParticleSystemTypeClass const *type)
{
    return type->VelocityPerturbationCoefficient;
}

void ParticleSystemClass::unknown_func_60c050()
{
    int i;
    if (!unknown_e4 && Particles.Count() == 0) {
        CoordStruct delta = TargetCoord - Position_Coord_004f3f40();
        int dx = delta.X;
        int dy = delta.Y;
        int dz = delta.Z;
        int total_dist = (int)Fast_Sqrt((double)dx * (double)dx + (double)dy * (double)dy + (double)dz * (double)dz);
        double dy_double = dy;
        double dx_double = dx;
        double horiz = dy_double * dy_double;
        int horiz_dist = (int)Fast_Sqrt(horiz + dx_double * dx_double);
        int clamped_z = dz;
        int clamped_x = dx;
        if (clamped_z >= total_dist) clamped_z = total_dist;
        if (clamped_z <= -total_dist) clamped_z = -total_dist;
        if (clamped_x >= horiz_dist) clamped_x = horiz_dist;
        if (clamped_x <= -horiz_dist) clamped_x = -horiz_dist;
        int num_particles = (int)((double)total_dist * Class->ParticlesPerCoord);
        float dist_f = (float)total_dist;
        float elevation = Fast_Acos((double)clamped_z / dist_f);
        float azimuth = Fast_Asin((double)clamped_x / horiz_dist);
        if (dy < 0) {
            azimuth = -azimuth;
        }
        Matrix3D mat;
        mat.Make_Identity();
        mat.Rotate_Z(azimuth);
        mat.Rotate_X(elevation);
        float velocity_accum = 0.0f;
        i = 0;
        if (num_particles > 0) {
            float num_particles_f = (float)num_particles;
            do {
                float frac = (float)i / num_particles_f;
                double angle = dist_f;
                angle *= frac;
                angle *= Class->SpiralDeltaPerCoord;
                double sine = unknown_sin_4ba480(angle);
                double cosine = unknown_cos_4ba4d0(angle);
                Vector3 spiral(0.0f, cosine, sine);
                spiral = mat * spiral;
                Vector3 scaled = spiral * Class->SpiralRadius;
                Vector3 tmp(((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->PositionPerturbationCoefficient,
                            ((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->PositionPerturbationCoefficient,
                            ((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->PositionPerturbationCoefficient);
                scaled += tmp;
                CoordStruct particle_pos = CoordStruct((int)scaled.X, (int)scaled.Y, (int)scaled.Z) + Lerp(Position_Coord_004f3f40(), TargetCoord, frac);
                ParticleClass *particle = Spawn_Particle(particle_pos, particle_pos);
                particle->unknown_fc = spiral;
                Vector3 move(((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->MovementPerturbationCoefficient,
                             ((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->MovementPerturbationCoefficient,
                             ((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) - 0.5) * Class->MovementPerturbationCoefficient);
                particle->unknown_fc += move;
                particle->unknown_fc = Normalize(particle->unknown_fc);
                float vp = ((Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10) + velocity_accum - 0.5)
                    * (Class->VelocityPerturbationCoefficient * 0.5);
                velocity_accum = (float)((((vp < Velocity_Limit(Class)) ? vp : Velocity_Limit(Class)) > -Class->MovementPerturbationCoefficient) ? ((vp < Velocity_Limit(Class)) ? vp : Velocity_Limit(Class)) : -Class->MovementPerturbationCoefficient);
                particle->Velocity = velocity_accum + particle->Class->Velocity;
                i++;
            } while (i < num_particles);
        }
        if (Class->Laser) {
            new LaserDrawClass(Position_Coord_004f3f40(), TargetCoord, 0, true, Class->LaserColor, RGBClass(0, 0, 0),
                               RGBClass(0, 0, 0), 10, false, true, 0.5f, 0.0f);
        }
        unknown_e4 = true;
    }
    for (i = 0; i < Particles.Count(); i++) {
        Particles[i]->unknown_func_609c90();
    }
    for (int j = Particles.Count() - 1; j >= 0; j--) {
        ParticleClass *particle = Particles[j];
        if (particle->unknown_121) {
            particle->unknown_slot60();
        }
    }
}
