// GraphicMenuShortcutItem::GraphicMenuShortcutItem(int id, Wstring const &keys) (0x004E0310)
// Splits the comma (or comma/semicolon) separated key names and keeps the key code of
// every name Parse_Shortcut_Key knows.
#include "shared/graphic_menu.hpp"
#include "shared/wstring.hpp"
// @ref ??0GraphicMenuItem@@QAE@H@Z=004e0120
// @ref ??_7GraphicMenuShortcutItem@@6B@=007a2bec
// @ref ??_7?$DynamicVectorClass@I@@6B@=0079c4dc
// @ref ??_C@_02GKDN@?0?$DL?$AA@=007d9f48
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?Parse_Shortcut_Key@@YIHABVWstring@@@Z=004e0410
int __fastcall Parse_Shortcut_Key(Wstring const &text);

GraphicMenuShortcutItem::GraphicMenuShortcutItem(int id, Wstring const &keys) : GraphicMenuItem(id)
{
    Wstring token;
    int position = keys.Get_Token(0, ",", token);
    while (token.Length() > 0) {
        int key = Parse_Shortcut_Key(token);
        if (key != 0) {
            Keys.Add(key);
        }
        position = keys.Get_Token(position, ",;", token);
        if (position == -1) {
            token.Release();
        }
    }
}
