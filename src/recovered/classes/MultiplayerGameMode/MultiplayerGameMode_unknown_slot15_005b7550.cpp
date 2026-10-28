// void MultiplayerGameMode::unknown_slot15(HWND list, DynamicVectorClass<MultiMission *> const *maps, MultiMission *selected) -- 0x005B7550
// Slot 15: the list-box counterpart of slot 14: empties the list
// (LB_RESETCONTENT), adds every multiplayer map with the custom message 0x4CD, keeps
// the map as item data (LB_SETITEMDATA) and selects the item of `selected`
// (LB_SETCURSEL). The elements are maps: MPCooperative's override 0x005A4B70
// reads their file names (+0x58).

void MultiplayerGameMode::unknown_slot15(HWND list, DynamicVectorClass<MultiMission *> const *maps, MultiMission *selected)
{
    SendMessageA(list, 0x184, 0, 0);                          // LB_RESETCONTENT
    for (int index = 0; index < maps->Count(); index++) {
        MultiMission *map = (*maps)[index];
        int item = SendMessageA(list, 0x4cd, 0, (LPARAM)map);
        if (map == selected) {
            SendMessageA(list, 0x186, item, 0);               // LB_SETCURSEL
        }
        SendMessageA(list, 0x19a, item, (LPARAM)map);         // LB_SETITEMDATA
    }
}
