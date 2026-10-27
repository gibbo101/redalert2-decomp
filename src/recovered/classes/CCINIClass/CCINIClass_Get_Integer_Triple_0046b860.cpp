// CCINIClass::Get_Integer_Triple (0x0046B860).
// Layout and behaviour: shared/ccini_class.hpp.

INIPoint3D CCINIClass::Get_Integer_Triple(char const *section, char const *entry, INIPoint3D const &defvalue)
{
    char buffer[512];
    INIPoint3D value = defvalue;
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        value.X = atoi(strtok(buffer, ","));
        value.Y = atoi(strtok(0, ","));
        value.Z = atoi(strtok(0, ","));
        return value;
    }
    return defvalue;
}
