// HouseTypeClass *__fastcall HouseTypeClass::Find_Or_Make(char const *name) (0x004FA350)
// The type with this ID, a new one when there is none, null for "<none>"/"none".
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??0HouseTypeClass@@QAE@PBD@Z=004f90f0

HouseTypeClass *__fastcall HouseTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < HouseTypes.Count(); index++) {
        if (_stricmp(HouseTypes[index]->ID, name) == 0) {
            return HouseTypes[index];
        }
    }
    return new HouseTypeClass(name);
}
