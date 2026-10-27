// int MultiplayerTeam::unknown_add_to_combo_5b9be0(HWND combo) -- 0x005B9BE0
// Adds the team name to a combo box (CB_ADDSTRING) with the team number as
// the item data (CB_SETITEMDATA); returns the new item's index.

int MultiplayerTeam::unknown_add_to_combo_5b9be0(HWND combo)
{
    int item = SendMessageA(combo, 0x143, 0, (long)Name.unknown_text_770430());   // CB_ADDSTRING
    SendMessageA(combo, 0x151, item, Number);                                     // CB_SETITEMDATA
    return item;
}
