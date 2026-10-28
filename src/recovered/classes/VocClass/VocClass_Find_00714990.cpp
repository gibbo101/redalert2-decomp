// VocClass *VocClass::Find(char const *name) (0x00714990): the sound effect
// with this name; 0 for none, "<none>" or an unknown name (name hypothesis).
#include "shared/voc_class.hpp"
#include "shared/crt_string.hpp"
// @ref __stricmp=00781f20
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc

VocClass *__fastcall VocClass::Find(char const *name)
{
    if (name != 0 && _stricmp(name, "<none>") != 0) {
        for (int index = 0; index < unknown_VocClass_list_00ad0818.Count(); index++) {
            if (_stricmp(name, unknown_VocClass_list_00ad0818[index]->Name()) == 0) {
                return unknown_VocClass_list_00ad0818[index];
            }
        }
    }
    return 0;
}
