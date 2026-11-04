// ParticleClass::ParticleClass(ParticleTypeClass *type, CoordStruct const &coord, CoordStruct const &target, ParticleSystemClass *system) (0x00608440)
// A particle of a type at a coordinate heading for a target: the direction
// is the normalized difference, the lifetime and colour come from the type
// (with some randomness), and it is placed above the ground.
#include "shared/particle.hpp"
#include "shared/map_view.hpp"
#include "shared/cd_timer.hpp"
#include "shared/crt_memory.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?unknown_ParticleClass_list_00a35e28@@3V?$DynamicVectorClass@PAVParticleClass@@@@A=00a35e28
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ??0RGBClass@@QAE@ABV0@0M@Z=0063cc80
// @ref ?unknown_slot103@ObjectClass@@UAEXABUCoordStruct@@@Z=005d51c0
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref _unknown_geometry_l=00a764e8
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3feb8637bd05af6c6800=007a7d20
// @ref __real@4@400c9c3c000000000000=007a7d28
// @ref __real@8@3fff8000000000000000=0079a708
// @ref ??_7ParticleClass@@6BIPersistStream@@@=007a7d5c
// @ref ??_7ParticleClass@@6BIRTTITypeInfo@@@=007a7d40
// @ref ??_7ParticleClass@@6BINoticeSink@@@=007a7d38
// @ref ??_7ParticleClass@@6BINoticeSource@@@=007a7d30

// The game's uniform random value in [a, b].
static inline double Random_Double(double a, double b)
{
    int value = unknown_id_source_a3d290->Random()(0, 0x7ffffffe);
    return (b - a) * (value * 4.656612877414201e-10) + a;
}

static inline Vector3 Normalized(Vector3 const &v)
{
    double length = unknown_sqrt_4ba410(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    if (length != 0.0) {
        return Vector3((float)(v.X / length), (float)(v.Y / length), (float)(v.Z / length));
    }
    return v;
}

ParticleClass::ParticleClass(ParticleTypeClass *type, CoordStruct const &coord, CoordStruct const &target,
                             ParticleSystemClass *system) :
    Class(type),
    unknown_b0(0, 0, 0),
    GasVelocity(0, 0, -1.0f),
    UnusedCoord1(0, 0, 0),
    Velocity(Class->Velocity),
    unknown_d8(target),
    unknown_e4(coord),
    unknown_f0(unknown_geometry_l),
    unknown_fc((float)(target.X - coord.X), (float)(target.Y - coord.Y), (float)(target.Z - coord.Z)),
    unknown_108((float)coord.X, (float)coord.Y, (float)coord.Z),
    System(system),
    unknown_11c(Class->StateAIAdvance),
    unknown_11d(0),
    unknown_11e(Class->StartStateAI),
    unknown_11f(Class->Translucency),
    unknown_120(false),
    unknown_121(false)
{
    AbstractClass::Create_ID();
    unknown_ParticleClass_list_00a35e28.Add(this);
    if (Class->BehavesLike == 1) {
        Velocity += (float)(unknown_id_source_a3d290->Random()() % 2);
    }
    unknown_11a = (short)Class->MaxDC;
    if (Class->BehavesLike == 4) {
        Lifetime = (unsigned short)(Class->MaxEC + abs(unknown_id_source_a3d290->Random()() % 10));
    } else {
        int random = unknown_id_source_a3d290->Random()();
        Lifetime = (unsigned short)(Class->MaxEC + abs(random % Class->MaxEC));
    }
    CoordStruct place(coord.X, coord.Y, coord.Z);
    if (place.Z <= Map.Unknown_0055A280(coord)) {
        place.Z = Map.Unknown_0055A280(coord);
    }
    unknown_slot103(place);
    unknown_fc = Normalized(unknown_fc);
    if (Class->Normalized) {
        CoordStruct delta(coord.X - target.X, coord.Y - target.Y, coord.Z - target.Z);
        float ax = (float)abs((int)(unknown_fc.X * Velocity));
        float ay = (float)abs((int)(unknown_fc.Y * Velocity));
        float steps = 9999.0f;
        if (ax > 1e-6) {
            steps = (float)(abs(delta.X) / ax);
        }
        if (ay > 1e-6) {
            float other = (float)(abs(delta.Y) / ay);
            if (!(steps < other)) {
                steps = other;
            }
        }
        unknown_11c = (char)(steps / (Class->FinalDamageState + 1) + 1.0);
    }
    if (Class->ColorList.Count() > 0) {
        if (Class->StartColor1.Red == 0 && Class->StartColor1.Green == 0 && Class->StartColor1.Blue == 0
            && Class->StartColor2.Red == 0 && Class->StartColor2.Green == 0 && Class->StartColor2.Blue == 0) {
            Color = Class->ColorList[0];
        } else {
            Color = RGBClass(Class->StartColor1, Class->StartColor2, (float)Random_Double(0.0, 1.0));
        }
    }
    ObjectClass::unknown_slot53(&place, 0);
}
