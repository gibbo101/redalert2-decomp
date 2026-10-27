// CCINIClass::Get_Float_Triple (0x0046B780).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref _atof=00782f66
extern "C" double __cdecl atof(char const *string);

INIVector3 CCINIClass::Get_Float_Triple(char const *section, char const *entry, INIVector3 const &defvalue)
{
    char buffer[512];
    INIVector3 value = defvalue;
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        value.X = atof(strtok(buffer, ","));
        value.Y = atof(strtok(0, ","));
        value.Z = atof(strtok(0, ","));
        return value;
    }
    return defvalue;
}
