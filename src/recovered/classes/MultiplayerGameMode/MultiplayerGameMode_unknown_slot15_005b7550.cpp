// void MultiplayerGameMode::unknown_slot15(HWND list, DynamicVectorClass<int> const *items, int selected) -- 0x005B7550
// Slot 15: the list-box counterpart of slot 14: empties the list
// (LB_RESETCONTENT), adds every item with the custom message 0x4CD, keeps
// the value as item data (LB_SETITEMDATA) and selects the item equal to
// `selected` (LB_SETCURSEL).

void MultiplayerGameMode::unknown_slot15(HWND list, DynamicVectorClass<int> const *items, int selected)
{
    SendMessageA(list, 0x184, 0, 0);                          // LB_RESETCONTENT
    for (int index = 0; index < items->Count(); index++) {
        int value = (*items)[index];
        int item = SendMessageA(list, 0x4cd, 0, value);
        if (value == selected) {
            SendMessageA(list, 0x186, item, 0);               // LB_SETCURSEL
        }
        SendMessageA(list, 0x19a, item, value);               // LB_SETITEMDATA
    }
}
