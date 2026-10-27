// ??1AITriggerTypeClass@@UAE@XZ (0x0041C6F0)
// Unlists the type.
#include "shared/ai_trigger_type.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260

AITriggerTypeClass::~AITriggerTypeClass()
{
    AITriggerTypes.Delete(this);
}
