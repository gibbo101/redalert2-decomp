// CCINIClass::Get_Buildings (0x0046AEA0; TibSun ccini.cpp): the building bitfield of a comma
// separated list: POWER, FACTORY, BARRACKS and RADAR set the top four bits, a building type ID
// its own bit (BuildingTypeClass::From_Name); defvalue when the entry is missing.
// @ref ??_C@_05CKDA@POWER?$AA@=007d1f40
// @ref ??_C@_07HGND@FACTORY?$AA@=007d1f38
// @ref ??_C@_08JHEE@BARRACKS?$AA@=007d1f2c
// @ref ??_C@_05BCPN@RADAR?$AA@=007d1f24

int CCINIClass::Get_Buildings(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    int pre;

    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        pre = 0;
        char *token = strtok(buffer, ",");
        while (token != 0 && *token != '\0') {
            if (!_stricmp(token, "POWER")) {
                pre |= 1L << (32 - 1);
            }
            if (!_stricmp(token, "FACTORY")) {
                pre |= 1L << (32 - 2);
            }
            if (!_stricmp(token, "BARRACKS")) {
                pre |= 1L << (32 - 3);
            }
            if (!_stricmp(token, "RADAR")) {
                pre |= 1L << (32 - 4);
            }
            int building = BuildingTypeClass::From_Name(token);
            if (building != -1) {
                pre |= (1L << building);
            }
            token = strtok(0, ",");
        }
    } else {
        pre = defvalue;
    }

    return pre;
}
