// int VocClass::From_Name(char const *name) (0x00714940): the index of the
// sound effect with this name, -1 if none.
#include "shared/voc_class.hpp"
#include "shared/crt_string.hpp"
// @ref __stricmp=00781f20
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c

int __fastcall VocClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < unknown_VocClass_list_00ad0818.Count(); index++) {
            if (_stricmp(name, unknown_VocClass_list_00ad0818[index]->Name()) == 0) {
                return index;
            }
        }
    }
    return -1;
}
