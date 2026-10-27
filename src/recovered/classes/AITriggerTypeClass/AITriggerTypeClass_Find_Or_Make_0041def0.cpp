// AITriggerTypeClass *__fastcall AITriggerTypeClass::Find_Or_Make(char const *name) (0x0041DEF0)
// The named AI trigger type, created when missing; 0 for "<none>" and "none".
#include "shared/ai_trigger_type.hpp"
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ??0AITriggerTypeClass@@QAE@PBD@Z=0041c5c0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

AITriggerTypeClass *__fastcall AITriggerTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name)) {
        return 0;
    }
    if (!_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < AITriggerTypes.Count(); index++) {
        if (!_stricmp(AITriggerTypes[index]->ID, name)) {
            return AITriggerTypes[index];
        }
    }
    return new AITriggerTypeClass(name);
}
