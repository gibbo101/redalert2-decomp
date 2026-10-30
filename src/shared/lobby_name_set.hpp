// The lobby's WideString name set: WOnline's chained hash dictionary (WolDictionary,
// shared/wol_dictionary.hpp) keyed by WideString with Hash_Wide_Name_005c2bf0; netshare.cpp
// fills it from a list box (0x005C5FF0) and removes names from it (0x005C6310). The
// template's out-of-line shrink and grow are 0x005CD9A0 and 0x005CDA50 (COMDATs at the unit's end).
#ifndef RA2_SHARED_LOBBY_NAME_SET_HPP
#define RA2_SHARED_LOBBY_NAME_SET_HPP

#include "shared/lobby.hpp"
#include "shared/wol_dictionary.hpp"

class LobbyNameSet : public WolDictionary<WideString, bool> {
public:
    LobbyNameSet() : WolDictionary<WideString, bool>(Hash_Wide_Name_005c2bf0) {}
};

// A list row's text as wide characters: wide rows (0x4CF) directly (0x4B6), narrow rows (0x4B7)
// converted through the caller's narrow buffer. Inline (no out-of-line copy): the list/name-set
// transfers 0x005C5FF0 and 0x005C6310 expand it.
inline void Get_List_Row_Text(HWND list, int index, wchar_t *text, char *narrow)
{
    if (SendMessageA(list, 0x4CF, index, 0)) {
        SendMessageA(list, 0x4B6, index, (LPARAM)text);
    } else {
        SendMessageA(list, 0x4B7, index, (LPARAM)narrow);
        Unknown_006FA0C0(text, narrow, -1);
    }
}

// Selects the list row whose text is the given wide text (0x4CA finds it, 0x186 selects it). Inline
// (expanded in 0x005C6310, after the name set's removal, which keeps its shrink out of line).
inline void Select_List_Row_Text(HWND list, wchar_t const *text)
{
    int index = SendMessageA(list, 0x4CA, -1, (LPARAM)text);
    if (index != -1) {
        SendMessageA(list, 0x186, index, 0);
    }
}

#endif
