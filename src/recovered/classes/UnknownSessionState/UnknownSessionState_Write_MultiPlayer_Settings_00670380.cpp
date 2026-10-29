// The dial method letters (0x007F320C: "T" tone, "P" pulse; Red Alert's DialMethodCheck).
extern char const *unknown_dial_methods_7f320c[2];
// @ref ?unknown_dial_methods_7f320c@@3PAPBDA=007f320c

// Red Alert's SessionClass::Write_MultiPlayer_Settings: saves the player and serial
// settings, the init strings and the phone book to RA2.INI.
void UnknownSessionState::Write_MultiPlayer_Settings()
{
    RawFileClass file("RA2.INI");

    unknown_ini_839740.Put_Int("MultiPlayer", "PhoneIndex", CurPhoneIdx);
    unknown_ini_839740.Put_Bool("MultiPlayer", "WOLLimitResolution", WOLLimitResolution);
    unknown_ini_839740.Put_Int("MultiPlayer", "LastNickSlot", LastNickSlot);
    unknown_ini_839740.Put_Unicode("MultiPlayer", "Handle", Unknown_006FA180(Handle));
    unknown_ini_839740.Put_Int("MultiPlayer", "Color", unknown_12c);
    unknown_ini_839740.Put_Int("MultiPlayer", "ColorEx", unknown_130);
    unknown_ini_839740.Put_HousesType("MultiPlayer", "Side", unknown_134);
    unknown_ini_839740.Put_Int("MultiPlayer", "SideEx", unknown_138);
    if (Mode) {
        unknown_ini_839740.Put_Int("MultiPlayer", "GameMode", Mode->Get_ID());
    } else {
        unknown_ini_839740.Put_Int("MultiPlayer", "GameMode", 0);
    }
    SkirmishOptions.Write(unknown_ini_839740, "Skirmish");
    LANOptions.Write(unknown_ini_839740, "LAN");
    WonlineOptions.Write(unknown_ini_839740, "WonlinePref");

    unknown_ini_839740.Clear("SerialDefaults");
    unknown_ini_839740.Put_String("SerialDefaults", "CallWaitString", SerialDefaults.CallWaitString);
    unknown_ini_839740.Put_Int("SerialDefaults", "CallWaitStringIndex", SerialDefaults.CallWaitStringIndex);
    unknown_ini_839740.Put_Int("SerialDefaults", "InitStringIndex", SerialDefaults.InitStringIndex);
    unknown_ini_839740.Put_String("SerialDefaults", "DialMethod", unknown_dial_methods_7f320c[SerialDefaults.DialMethod]);
    unknown_ini_839740.Put_Int("SerialDefaults", "Baud", SerialDefaults.Baud);
    unknown_ini_839740.Put_Int("SerialDefaults", "IRQ", SerialDefaults.IRQ);
    unknown_ini_839740.Put_Int("SerialDefaults", "Port", SerialDefaults.Port, 1);
    unknown_ini_839740.Put_Int("SerialDefaults", "Compression", SerialDefaults.Compression);
    unknown_ini_839740.Put_Int("SerialDefaults", "ErrorCorrection", SerialDefaults.ErrorCorrection);
    unknown_ini_839740.Put_String("SerialDefaults", "ModemName", SerialDefaults.ModemName);

    unknown_ini_839740.Clear("InitStrings");
    for (int index = 0; index < InitStrings.Count(); index++) {
        char buf[10];
        wsprintfA(buf, "%03d", index);
        unknown_ini_839740.Put_String("InitStrings", buf, InitStrings[index]);
    }

    unknown_ini_839740.Clear("PhoneBook");
    for (int i = PhoneBook.Count() - 1; i >= 0; i--) {
        char buf[128];
        char entrytext[10];
        wsprintfA(buf, "%s|%s|%x|%d|%d|%d|%d|%s|%d|%d|%s",
                  PhoneBook[i]->Name,
                  PhoneBook[i]->Number,
                  PhoneBook[i]->Settings.Port,
                  PhoneBook[i]->Settings.IRQ,
                  PhoneBook[i]->Settings.Baud,
                  PhoneBook[i]->Settings.Compression,
                  PhoneBook[i]->Settings.ErrorCorrection,
                  unknown_dial_methods_7f320c[PhoneBook[i]->Settings.DialMethod],
                  PhoneBook[i]->Settings.InitStringIndex,
                  PhoneBook[i]->Settings.CallWaitStringIndex,
                  PhoneBook[i]->Settings.CallWaitString);
        wsprintfA(entrytext, "%03d", i);
        unknown_ini_839740.Put_String("PhoneBook", entrytext, buf);
    }

    unknown_ini_839740.Save(file, false);
}
// @ref ??_C@_08MAFF@GameMode?$AA@=007f34d8
// @ref ??_C@_0CB@NMCE@?$CFs?$HM?$CFs?$HM?$CFx?$HM?$CFd?$HM?$CFd?$HM?$CFd?$HM?$CFd?$HM?$CFs?$HM?$CFd?$HM?$CFd?$HM?$CFs@=007f388c
// @ref ??_C@_09BCMM@PhoneBook?$AA@=007f3558
// @ref ??_C@_04KAJP@?$CF03d?$AA@=007cf33c
// @ref ??_C@_0M@LJHH@InitStrings?$AA@=007f3564
// @ref ??_C@_09EHPD@ModemName?$AA@=007f35f0
// @ref ??_C@_0BA@NIDC@ErrorCorrection?$AA@=007f35b0
// @ref ??_C@_0M@MOML@Compression?$AA@=007f35c0
// @ref ??_C@_04CEAI@Port?$AA@=007f35d8
// @ref ??_C@_03MHH@IRQ?$AA@=007f35d4
// @ref ??_C@_04IPGK@Baud?$AA@=007f35cc
// @ref ??_C@_0L@IPGK@DialMethod?$AA@=007f35a4
// @ref ??_C@_0BA@OGHJ@InitStringIndex?$AA@=007f3594
// @ref ??_C@_0BE@FIJL@CallWaitStringIndex?$AA@=007f3580
// @ref ??_C@_0P@KBNH@CallWaitString?$AA@=007f3570
// @ref ??_C@_0P@HEME@SerialDefaults?$AA@=007f35e0
// @ref ??_C@_0M@BIDM@WonlinePref?$AA@=007f35fc
// @ref ??_C@_03OPEA@LAN?$AA@=007f3608
// @ref ??_C@_08GGBF@Skirmish?$AA@=007f360c
// @ref ??_C@_06HKOL@SideEx?$AA@=007f3650
// @ref ??_C@_04LJDI@Side?$AA@=007cdd8c
// @ref ??_C@_07EDGH@ColorEx?$AA@=007f3658
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_06ILKP@Handle?$AA@=007f3660
// @ref ??_C@_0N@FPHD@LastNickSlot?$AA@=007f3668
// @ref ??_C@_0BD@FJLN@WOLLimitResolution?$AA@=007f3678
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_0L@JMMI@PhoneIndex?$AA@=007f3698
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ?Write@UnknownGameOptions@@QAEXAAVCCINIClass@@PBD@Z=00670270
