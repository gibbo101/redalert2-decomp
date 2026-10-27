// SuperWeaponTypeClass *__fastcall SuperWeaponTypeClass::Find_Or_Make(char const *name) (0x0069F820)
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??0SuperWeaponTypeClass@@QAE@PBD@Z=0069f000

SuperWeaponTypeClass *__fastcall SuperWeaponTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < SuperWeaponTypes.Count(); index++) {
        if (_stricmp(SuperWeaponTypes[index]->ID, name) == 0) {
            return SuperWeaponTypes[index];
        }
    }
    return new SuperWeaponTypeClass(name);
}
