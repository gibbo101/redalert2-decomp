// void MultiplayerGameMode::unknown_slot14(HWND combo, DynamicVectorClass<int> const *items, int selected) -- 0x005B74E0
// Slot 14: refills a combo box (0x006007F0 resets it) with the given items
// (each added as the item text and kept as its item data) and selects the
// item equal to `selected`.
// @ref ?unknown_reset_combo_6007f0@@YIXPAUHWND__@@@Z=006007f0
// @ref __imp__SendMessageA@16=0079a4a0

void __fastcall unknown_reset_combo_6007f0(HWND combo);

void MultiplayerGameMode::unknown_slot14(HWND combo, DynamicVectorClass<int> const *items, int selected)
{
    unknown_reset_combo_6007f0(combo);
    for (int index = 0; index < items->Count(); index++) {
        int value = (*items)[index];
        int item = SendMessageA(combo, 0x143, 0, value);      // CB_ADDSTRING
        if (value == selected) {
            SendMessageA(combo, 0x14e, item, 0);              // CB_SETCURSEL
        }
        SendMessageA(combo, 0x151, item, value);              // CB_SETITEMDATA
    }
}
