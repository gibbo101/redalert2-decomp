// void __fastcall Restore_List_Selection_005c6310(HWND list, LobbyNameSet *names) (0x005C6310)
// Selects the list rows whose text is in the name set: every such row of a multiple-selection list,
// or for a single-selection list the row of one name taken out of the set.
#include "shared/lobby_name_set.hpp"

void __fastcall Restore_List_Selection_005c6310(HWND list, LobbyNameSet *names)
{
    wchar_t text[0x400];
    char narrow[0x400];
    int count = SendMessageA(list, 0x18B, 0, 0);
    WideString name;
    if (count != 0) {
        LONG style = GetWindowLongA(list, GWL_STYLE);
        if (style & 8) {
            for (int i = 0; i < count; i++) {
                Get_List_Row_Text(list, i, text, narrow);
                name = text;
                if (names->Contains(name)) {
                    SendMessageA(list, 0x185, 1, i);
                }
            }
        } else if (!(style & 0x4000)) {
            bool value;
            if (names->Remove_Any(name, value)) {
                wcscpy(text, name.Get());
                Select_List_Row_Text(list, text);
            }
        }
    }
}
