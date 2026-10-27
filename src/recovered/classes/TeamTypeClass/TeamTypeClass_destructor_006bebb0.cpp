// TeamTypeClass::~TeamTypeClass() (0x006BEBB0)
// Detaches the type from everything and leaves the team type and abstract
// lists. The scalar deleting destructor (0x006C0280) expands this body.
#include "shared/team_type.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

TeamTypeClass::~TeamTypeClass()
{
    Unknown_006ECB90(this, true);
    TeamTypes.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
}
