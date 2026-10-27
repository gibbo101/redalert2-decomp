// RulesClass::MPlayer (0x0064B690)
// @ref ??_C@_05BALL@Bases?$AA@=007f159c
// @ref ??_C@_05COBC@Money?$AA@=007d3870
// @ref ??_C@_06HOMM@Crates?$AA@=007f1584
// @ref ??_C@_06IMPE@Shroud?$AA@=007f15a4
// @ref ??_C@_08CNHP@MinMoney?$AA@=007f1630
// @ref ??_C@_08HEJL@FogOfWar?$AA@=007f1508
// @ref ??_C@_08HOBA@MaxMoney?$AA@=007f1624
// @ref ??_C@_09BNKA@ShortGame?$AA@=007f1538
// @ref ??_C@_09FKED@TechLevel?$AA@=007da8bc
// @ref ??_C@_09HECM@AIPlayers?$AA@=007f15cc
// @ref ??_C@_09NLF@UnitCount?$AA@=007f15f8
// @ref ??_C@_09OAAF@GameSpeed?$AA@=007e89c0
// @ref ??_C@_0BC@JNEJ@BridgeDestruction?$AA@=007f15b8
// @ref ??_C@_0BE@NIHF@SuperWeaponsAllowed?$AA@=007f1524
// @ref ??_C@_0L@GEBB@ShadowGrow?$AA@=007f15ac
// @ref ??_C@_0N@CDP@AIDifficulty?$AA@=007f15d8
// @ref ??_C@_0N@EJOH@MCVRedeploys?$AA@=007f14f8
// @ref ??_C@_0N@FAGI@MaxUnitCount?$AA@=007f15e8
// @ref ??_C@_0N@IGGL@BuildOffAlly?$AA@=007f1514
// @ref ??_C@_0N@NILP@MinUnitCount?$AA@=007f1604
// @ref ??_C@_0O@CCKF@TiberiumGrows?$AA@=007f158c
// @ref ??_C@_0O@DKMN@MultiEngineer?$AA@=007f1554
// @ref ??_C@_0O@JMPE@AlliesAllowed?$AA@=007f1544
// @ref ??_C@_0P@BAHN@HarvesterTruce?$AA@=007f1564
// @ref ??_C@_0P@JGBP@CaptureTheFlag?$AA@=007f1574
// @ref ??_C@_0P@MGII@MoneyIncrement?$AA@=007f1614
// @ref _RulesSection_MultiplayerDialogSettings=007a905c
// @ref ??_C@_0BK@IOIK@MultiplayerDialogSettings?$AA@=007e5f04
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::MPlayer(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_MultiplayerDialogSettings)) {
        MinMoney = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "MinMoney", MinMoney);
        Money = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "Money", Money);
        MaxMoney = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "MaxMoney", MaxMoney);
        MoneyIncrement = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "MoneyIncrement", MoneyIncrement);
        MinUnitCount = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "MinUnitCount", MinUnitCount);
        UnitCount = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "UnitCount", UnitCount);
        MaxUnitCount = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "MaxUnitCount", MaxUnitCount);
        TechLevel = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "TechLevel", TechLevel);
        GameSpeed = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "GameSpeed", GameSpeed);
        AIDifficulty = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "AIDifficulty", AIDifficulty);
        AIPlayers = ini.Get_Int(RulesSection_MultiplayerDialogSettings, "AIPlayers", AIPlayers);
        BridgeDestruction = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "BridgeDestruction", BridgeDestruction);
        ShadowGrow = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "ShadowGrow", ShadowGrow);
        Shroud = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "Shroud", Shroud);
        Bases = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "Bases", Bases);
        TiberiumGrows = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "TiberiumGrows", TiberiumGrows);
        Crates = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "Crates", Crates);
        CaptureTheFlag = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "CaptureTheFlag", CaptureTheFlag);
        HarvesterTruce = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "HarvesterTruce", HarvesterTruce);
        MultiEngineer = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "MultiEngineer", MultiEngineer);
        unknown_111d = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "AlliesAllowed", unknown_111d);
        ShortGame = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "ShortGame", ShortGame);
        SuperWeaponsAllowed = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "SuperWeaponsAllowed", SuperWeaponsAllowed);
        BuildOffAlly = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "BuildOffAlly", BuildOffAlly);
        FogOfWar = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "FogOfWar", FogOfWar);
        MCVRedeploys = ini.Get_Bool(RulesSection_MultiplayerDialogSettings, "MCVRedeploys", MCVRedeploys);
        return true;
    }
    return false;
}
