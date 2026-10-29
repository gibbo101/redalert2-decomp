void UnknownGameOptions::Write(CCINIClass &ini, char const *section)
{
    ini.Put_Int(section, "GameMode", GameMode);
    ini.Put_Int(section, "ScenIndex", ScenIndex);
    ini.Put_Int(section, "GameSpeed", GameSpeed);
    ini.Put_Int(section, "Credits", Credits);
    ini.Put_Int(section, "UnitCount", UnitCount);
    ini.Put_Bool(section, "ShortGame", ShortGame);
    ini.Put_Bool(section, "SuperWeaponsAllowed", SuperWeaponsAllowed);
    ini.Put_Bool(section, "BuildOffAlly", BuildOffAlly);
    ini.Put_Bool(section, "MCVRepacks", MCVRepacks);
    ini.Put_Bool(section, "CratesAppear", CratesAppear);
    for (int i = 1; i < 8; i++) {
        char buffer[16];
        sprintf(buffer, "Slot%02d", i);
        ini.Put_Integers(section, buffer, Slots[i][0], Slots[i][1], Slots[i][2]);
    }
}
// @ref ??_C@_08EIHP@Slot?$CF02d?$AA@=007f34a4
// @ref ??_C@_08MAFF@GameMode?$AA@=007f34d8
// @ref ??_C@_09NMFM@ScenIndex?$AA@=007f34cc
// @ref ??_C@_0L@GIMI@MCVRepacks?$AA@=007f34c0
// @ref ??_C@_0N@FPON@CratesAppear?$AA@=007f34b0
// @ref ??_C@_0N@IGGL@BuildOffAlly?$AA@=007f1514
// @ref ??_C@_0BE@NIHF@SuperWeaponsAllowed?$AA@=007f1524
// @ref ??_C@_09BNKA@ShortGame?$AA@=007f1538
// @ref ??_C@_09NLF@UnitCount?$AA@=007f15f8
// @ref ??_C@_07NGJJ@Credits?$AA@=007da8b4
// @ref ??_C@_09OAAF@GameSpeed?$AA@=007e89c0
