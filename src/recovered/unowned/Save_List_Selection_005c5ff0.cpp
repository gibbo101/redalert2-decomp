// @ref ?Grow_Table@?$WolDictionary@VWideString@@_N@@QAEXXZ=005cda50
// Save the selected list rows in the lobby name dictionary (0x005C5FF0).
#include "shared/lobby_name_set.hpp"

void __fastcall Save_List_Selection_005c5ff0(HWND list, LobbyNameSet *names)
{
    int count = SendMessageA(list, 0x18B, 0, 0);
    WideString name;
    wchar_t text[0x400];
    char narrow[0x400];
    if (count == 0) return;
    {
        LONG style = GetWindowLongA(list, GWL_STYLE);
        if (style & 8) {
            for (int index = 0; index < count; ++index) {
                if (SendMessageA(list, 0x187, index, 0)) {
                    Get_List_Row_Text(list, index, text, narrow);
                    name = text;
                    bool selected = true;
                    names->Add(name, selected);
                }
            }
        } else if (!(style & 0x4000)) {
            int index = SendMessageA(list, 0x188, 0, 0);
            if (index >= 0) {
                text[0] = 0;
                Get_List_Row_Text(list, index, text, narrow);
                name = text;
                bool selected = true;
                names->Add(name, selected);
            }
        }
    }
}
