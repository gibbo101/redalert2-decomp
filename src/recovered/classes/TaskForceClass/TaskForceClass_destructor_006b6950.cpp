// TaskForceClass::~TaskForceClass() (0x006B6950)
// Releases references to the task force and removes it from TaskForces.
#include "shared/task_force.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

TaskForceClass::~TaskForceClass()
{
    Unknown_006ECB90(this, true);
    TaskForces.Delete(this);
}
