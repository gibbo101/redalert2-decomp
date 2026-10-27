// CCINIClass::Get_Level (0x0046C9D0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?LevelNames@@3PAPBDA=007d1a98
// @ref ??_C@_04COF@None?$AA@=007ce9b4
// @ref ??_C@_06BILL@Normal?$AA@=007d1b30
// @ref ??_C@_06BEKF@Strong?$AA@=007d1aa4

LevelType CCINIClass::Get_Level(char const *section, char const *entry, LevelType defvalue)
{
    char buffer[128];
    Get_String(section, entry, LevelNames[defvalue], buffer, sizeof(buffer));
    char *token = strtok(buffer, ",");
    if (_stricmp(token, "None") == 0) {
        return LEVEL_NONE;
    }
    if (_stricmp(token, "Normal") == 0) {
        return LEVEL_NORMAL;
    }
    if (_stricmp(token, "Strong") == 0) {
        return LEVEL_STRONG;
    }
    return defvalue;
}
