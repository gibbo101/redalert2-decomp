// ObjectTypeClass *__fastcall ObjectTypeClass::Find_From_Name(char const *name) (0x005D7EA0)
// The object type whose ID matches name (case-insensitive), else null.
// (The inventory splits this body at 0x005D7EB3, inside the loop's first
// instruction bytes; the function runs from 0x005D7EA0 to the ret at
// 0x005D7EE2.)
#include "shared/object_type.hpp"
// @ref __stricmp=00781f20
// @ref ?ObjectTypes@ObjectTypeClass@@2V?$DynamicVectorClass@PAVObjectTypeClass@@@@A=00a72f90

extern "C" int __cdecl _stricmp(char const *string1, char const *string2);

ObjectTypeClass *__fastcall ObjectTypeClass::Find_From_Name(char const *name)
{
    for (int index = 0; index < ObjectTypes.Count(); index++) {
        if (_stricmp(ObjectTypes[index]->ID, name) == 0) {
            return ObjectTypes[index];
        }
    }
    return 0;
}
