// MP_Set_Dialog_Item_Number_005AAB80 (0x005AAB80): CampScor.cpp's unknown_set_dialog_item_number_467240.

void __fastcall MP_Set_Dialog_Item_Number_005AAB80(HWND dialog, int id, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    HWND item = GetDlgItem(dialog, id);
    SendMessageA(item, 0x4b2, 0, (long)text);
}
