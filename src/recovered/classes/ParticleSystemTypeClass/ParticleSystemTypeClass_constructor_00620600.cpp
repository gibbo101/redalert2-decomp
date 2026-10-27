#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/particle_system.hpp"
ParticleSystemTypeClass::ParticleSystemTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name), HoldsWhat(-1), Spawns(false), SpawnFrames(1),
    Slowdown(0), ParticleCap(50), SpawnRadius(0), SpawnCutoff(0), SpawnTranslucencyCutoff(0),
    BehavesLike(-1), Lifetime(-1), SpawnDirection(0, 0, 0), ParticlesPerCoord(0.1),
    SpiralDeltaPerCoord(0.025), SpiralRadius(25.0), PositionPerturbationCoefficient(0),
    MovementPerturbationCoefficient(0), VelocityPerturbationCoefficient(0), SpawnSparkPercentage(0),
    SparkSpawnFrames(0), LightSize(0), Laser(false), OneFrameLight(false)
{
    AbstractClass::Create_ID();
    ParticleSystemTypes.Add(this);
    unknown_204 = true;
}
