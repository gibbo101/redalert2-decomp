// VoxClass *VoxClass::Find(char const *name) (0x007166C0): the VoxClass of a
// name; 0 for a null name, "<none>" or no match.
#include "shared/vox_speech.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20

VoxClass *__fastcall VoxClass::Find(char const *name)
{
    if (name != 0 && _stricmp(name, "<none>") != 0) {
        for (int index = 0; index < unknown_VoxClass_list_00ad0930.Count(); index++) {
            if (_stricmp(name, unknown_VoxClass_list_00ad0930[index]->Name) == 0) {
                return unknown_VoxClass_list_00ad0930[index];
            }
        }
    }
    return 0;
}
