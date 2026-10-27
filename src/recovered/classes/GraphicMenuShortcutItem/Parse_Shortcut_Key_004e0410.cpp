// int __fastcall Parse_Shortcut_Key(Wstring const &text) (0x004E0410): the key code of a
// shortcut name: optional "ctrl-" (0x200), "alt-" (0x400) and "shift-" (0x100) prefixes,
// then one character (its code minus 0x20) or a name from the table at 0x007D9EF8
// ("esc", "backspace"); 0 when the name is empty or unknown. Name is a hypothesis.
// @ref ?KeyNames_7d9ef8@@3QBUKeyName@@B=007d9ef8
// @ref ??_C@_05HJN@ctrl?9?$AA@=007d9f5c
// @ref ??_C@_04INGC@alt?9?$AA@=007d9f54
// @ref ??_C@_06KHFB@shift?9?$AA@=007d9f4c
#include "shared/graphic_menu.hpp"

struct KeyName {
    char const *Name;
    int Code;
};
extern KeyName const KeyNames_7d9ef8[2];       // 0x007D9EF8 {"esc", 0x1B}, {"backspace", 8}

int __fastcall Parse_Shortcut_Key(Wstring const &text)
{
    int key = 0;
    Wstring name(text);
    name.To_Lower();
    Wstring prefix(name);
    prefix.Truncate(5);
    if (prefix == "ctrl-") {
        key = 0x200;
        name.Remove(0, 5);
    }
    prefix = name;
    prefix.Truncate(4);
    if (prefix == "alt-") {
        key |= 0x400;
        name.Remove(0, 4);
    }
    prefix = name;
    prefix.Truncate(6);
    if (prefix == "shift-") {
        key |= 0x100;
        name.Remove(0, 6);
    }
    int value = 0;
    switch (name.Length()) {
        case 0:
            break;
        case 1:
            value = name.Get_Char(0) - ' ';
            break;
        default: {
            int index;
            for (index = 1; index >= 0; index--) {
                if (!(name != KeyNames_7d9ef8[index].Name)) {
                    break;
                }
            }
            if (index >= 0) {
                value = KeyNames_7d9ef8[index].Code;
            }
            break;
        }
    }
    if (value != 0) {
        key |= value;
    } else {
        key = 0;
    }
    return key;
}
