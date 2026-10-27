// GraphicMenuItem *__fastcall Create_Shortcut_Item(Wstring const &section, INIClass &ini)
// (0x004E0250): a GraphicMenuShortcutItem from a menu INI section's ID (none for -1)
// and Keys. Name is a hypothesis; the argument shapes follow the original: the ID key
// is an explicit Wstring temporary (pushed as the constructor's result), the Keys
// entry and its default convert implicitly (their temporaries' addresses are pushed).
// @ref ??_C@_02GMH@ID?$AA@=007d52a8
// @ref ??_C@_04NLJJ@Keys?$AA@=007d9f18
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ??0GraphicMenuShortcutItem@@QAE@HABVWstring@@@Z=004e0310
#include "shared/ini_class.hpp"
#include "shared/graphic_menu.hpp"

extern char unknown_string_83c55c[];

GraphicMenuItem *__fastcall Create_Shortcut_Item(Wstring const &section, INIClass &ini)
{
    int id = ini.Get_Int(section, Wstring("ID"), -1);
    if (id == -1) {
        return 0;
    }
    Wstring keys;
    ini.Get_String(section, "Keys", unknown_string_83c55c, keys);
    return new GraphicMenuShortcutItem(id, keys);
}
