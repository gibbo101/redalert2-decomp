// TriggerTypeClass *__fastcall TriggerTypeClass::Find_Or_Make(char const *name) (0x006EECC0)
// The named trigger type, created when missing; 0 for "<none>" and "none".
#include "shared/trigger_type.hpp"
// @ref ??0TriggerTypeClass@@QAE@PBD@Z=006edeb0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

TriggerTypeClass *__fastcall TriggerTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < TriggerTypes.Count(); index++) {
        if (!_stricmp(TriggerTypes[index]->ID, name)) {
            return TriggerTypes[index];
        }
    }
    return new TriggerTypeClass(name);
}
