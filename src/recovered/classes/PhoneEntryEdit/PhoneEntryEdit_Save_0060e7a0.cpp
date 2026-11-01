// 0x0060E7A0
void PhoneEntryEdit::Save()
{
    bool custom;

    HWND handle = GetDlgItem(_Dialog, 0x5E5);
    if (handle != 0) {
        SendMessageA(handle, 0x4B3, sizeof(Phone->Name) / sizeof(Phone->Name[0]), (LPARAM)Phone->Name);
        if (wcslen(Phone->Name) > 0) {
            _wcsupr(Phone->Name);
        } else {
            wcscpy(Phone->Name, StringTable::Load_String("TXT_NONAME", 0, "D:\\Ra2\\PhoneEd.cpp", 0x2F5));
        }
    }
    Debug_Printf("Name: %ls\n", Phone->Name);
    handle = GetDlgItem(_Dialog, 0x5DF);
    if (handle != 0) {
        SendMessageA(handle, 0x4B5, 21, (LPARAM)Phone->Number);
    }
    Debug_Printf("Number: %s\n", Phone->Number);
    handle = GetDlgItem(_Dialog, 0x664);
    if (handle) {
        custom = SendMessageA(handle, 0xF0, 0, 0) == 1;
    } else {
        custom = false;
    }
    if (custom == true) {
        Phone->Settings = TempSettings;
    } else {
        Phone->Settings.Port = 0;
        Phone->Settings.IRQ = -1;
        Phone->Settings.Baud = -1;
        Phone->Settings.DialMethod = 0;
        Phone->Settings.InitStringIndex = -1;
        Phone->Settings.CallWaitStringIndex = 3;
        Phone->Settings.CallWaitString[0] = 0;
    }
    Debug_Printf("Settings: Port %d, Baud %d\n", Phone->Settings.Port, Phone->Settings.Baud);
}
// @ref ??_C@_0BD@PIKI@D?3?2Ra2?2PhoneEd?4cpp?$AA@=007eb8f8
// @ref ??_C@_0BM@MDDL@Settings?3?5Port?5?$CFd?0?5Baud?5?$CFd?6?$AA@=007eb918
// @ref ??_C@_0L@DFNB@Name?3?5?$CFls?6?$AA@=007e2028
// @ref ??_C@_0L@JPAF@TXT_NONAME?$AA@=007eb8ec
// @ref ??_C@_0M@IELE@Number?3?5?$CFs?6?$AA@=007eb934
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __wcsupr=00796ef6
// @ref _wcscpy=00783689
// @ref _wcslen=00783605
