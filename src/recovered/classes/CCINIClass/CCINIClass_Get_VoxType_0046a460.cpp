// CCINIClass::Get_VoxType (0x0046A460).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Find_Index@VoxClass@@SIHPBD@Z=00716640

int CCINIClass::Get_VoxType(char const *section, char const *entry, int defvalue) const
{
    char buffer[100];
    Get_String(section, entry, "", buffer, sizeof(buffer));
    if (strlen(buffer) != 0) {
        return VoxClass::Find_Index(buffer);
    }
    return defvalue;
}
