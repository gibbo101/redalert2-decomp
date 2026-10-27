// CCINIClass::Get_SuperWeaponType (0x0046A410).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Find_Index@SuperWeaponTypeClass@@SIHPBD@Z=0069f790
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338

int CCINIClass::Get_SuperWeaponType(char const *section, char const *entry, int defvalue) const
{
    char empty[28];
    char buffer[32];
    char const *defname;
    if (defvalue != -1) {
        defname = SuperWeaponTypes[defvalue]->ID;
    } else {
        empty[0] = '\0';
        defname = empty;
    }
    Get_String(section, entry, defname, buffer, sizeof(buffer));
    return SuperWeaponTypeClass::Find_Index(buffer);
}
