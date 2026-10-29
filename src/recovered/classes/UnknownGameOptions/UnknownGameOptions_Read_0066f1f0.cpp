void UnknownGameOptions::Read(CCINIClass &ini, char const *section, int other_slots, int first_slot)
{
    GameMode = ini.Get_Int(section, "GameMode", MultiplayerGameMode::unknown_first_mode_5b6ec0()->Get_ID());
    ScenIndex = ini.Get_Int(section, "ScenIndex", 0);
    GameSpeed = ini.Get_Int(section, "GameSpeed", Rules->GameSpeed);
    Credits = ini.Get_Int(section, "Credits", Rules->Money);
    UnitCount = ini.Get_Int(section, "UnitCount", Rules->UnitCount);
    ShortGame = ini.Get_Bool(section, "ShortGame", Rules->ShortGame);
    SuperWeaponsAllowed = ini.Get_Bool(section, "SuperWeaponsAllowed", Rules->SuperWeaponsAllowed);
    BuildOffAlly = ini.Get_Bool(section, "BuildOffAlly", Rules->BuildOffAlly);
    MCVRepacks = ini.Get_Bool(section, "MCVRepacks", Rules->MCVRedeploys);
    CratesAppear = ini.Get_Bool(section, "CratesAppear", Rules->Crates);
    for (int i = 1; i < 8; i++) {
        char buffer[16];
        sprintf(buffer, "Slot%02d", i);
        int first = (i == 1) ? first_slot : other_slots;
        int second = -2;
        int third = -2;
        ini.Get_Integers(section, buffer, first, second, third);
        Slots[i][0] = first;
        Slots[i][1] = second;
        Slots[i][2] = third;
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
