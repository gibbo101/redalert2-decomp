#define TYPELIST_IMPLEMENT_DEFAULT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/particle_system.hpp"
ParticleTypeClass::ParticleTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name), NextParticleOffset(0, 0, 0), XVelocity(1), YVelocity(1),
    MinZVelocity(0), ZVelocityRange(1), ColorSpeed(0), MaxDC(0), MaxEC(1), Warhead(0),
    Damage(0), StartFrame(0), NumLoopFrames(1), Translucency(0), WindEffect(0),
    Velocity(0), Deacc(0), Radius(0), DeleteOnStateLimit(false), EndStateAI(0),
    StartStateAI(0), StateAIAdvance(4), FinalDamageState(0), Translucent25State(255),
    Translucent50State(255), Normalized(false), NextParticle(-1), BehavesLike(-1)
{
    ParticleTypes.Add(this);
    unknown_objects_ac0cb0.Add(this);
    unknown_204 = false;
}
