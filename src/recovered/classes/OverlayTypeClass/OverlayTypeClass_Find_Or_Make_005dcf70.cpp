// static OverlayTypeClass *__fastcall OverlayTypeClass::Find_Or_Make(char const *name) (0x005DCF70)
// The type with this ID, else a new one; null for "<none>" and "none".
#include "shared/overlay_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0OverlayTypeClass@@QAE@PBD@Z=005dc5a0

OverlayTypeClass *__fastcall OverlayTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < OverlayTypes.Count(); index++) {
        if (_stricmp(OverlayTypes[index]->ID, name) == 0) {
            return OverlayTypes[index];
        }
    }
    return new OverlayTypeClass(name);
}
