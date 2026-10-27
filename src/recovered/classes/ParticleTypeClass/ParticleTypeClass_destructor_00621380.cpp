#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/particle_system.hpp"
ParticleTypeClass::~ParticleTypeClass()
{
    Unknown_006ECB90(this, true);
    unknown_objects_ac0cb0.Delete(this);
    ParticleTypes.Delete(this);
}
