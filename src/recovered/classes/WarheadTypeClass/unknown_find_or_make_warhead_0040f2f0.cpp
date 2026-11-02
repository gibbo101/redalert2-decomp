// int unknown_find_or_make_warhead_0040f2f0(char const *name) (0x0040F2F0)
// Index of the warhead type with this ID in the unit's list 0x00839B00 (-1 for
// "<none>" and "none"); an unknown ID makes a new type and returns its index.
// No direct callers.
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref __stricmp=00781f20
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0WarheadTypeClass@@QAE@PBD@Z=00720100
#include "shared/warhead_type.hpp"
#include "shared/crt_string.hpp"

int __fastcall unknown_find_or_make_warhead_0040f2f0(char const *name)
{
    if (_stricmp(name, "<none>") == 0 || _stricmp(name, "none") == 0) {
        return -1;
    }
    for (int index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
        if (_stricmp(name, unknown_WarheadTypeClass_list_00839b00[index]->ID) == 0) {
            return index;
        }
    }
    return unknown_WarheadTypeClass_list_00839b00.ID(new WarheadTypeClass(name));
}
