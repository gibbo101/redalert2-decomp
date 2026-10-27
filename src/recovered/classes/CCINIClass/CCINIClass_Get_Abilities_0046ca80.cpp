// CCINIClass::Get_Abilities (0x0046CA80).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Ability_From_Name@@YIHPBD@Z=00713300

AbilitiesStruct CCINIClass::Get_Abilities(char const *section, char const *entry, AbilitiesStruct const &defvalue)
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        AbilitiesStruct abilities;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            int ability = Ability_From_Name(token);
            if (ability != -1) {
                abilities.Ability[ability] = true;
            }
        }
        return abilities;
    }
    return defvalue;
}
