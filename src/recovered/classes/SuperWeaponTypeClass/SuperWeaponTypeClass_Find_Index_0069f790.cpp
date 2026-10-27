// int __fastcall SuperWeaponTypeClass::Find_Index(char const *name) (0x0069F790)

int __fastcall SuperWeaponTypeClass::Find_Index(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < SuperWeaponTypes.Count(); index++) {
            if (_stricmp(SuperWeaponTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
