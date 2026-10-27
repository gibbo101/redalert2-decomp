// TriggerTypeClass *__fastcall TriggerTypeClass::From_Name(char const *name) (0x006EE350)
#include "shared/object.hpp"

TriggerTypeClass *__fastcall TriggerTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < TriggerTypes.Count(); index++) {
            if (!_stricmp(TriggerTypes[index]->ID, name) ||
                !_stricmp(TriggerTypes[index]->Name, name)) {
                return TriggerTypes[index];
            }
        }
    }
    return 0;
}
