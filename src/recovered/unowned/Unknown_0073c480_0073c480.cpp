// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_01FLCE@L?$AA@=007fd5f8
#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
bool __fastcall Unknown_005c9320(NodeNameType *entry);
Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(NodeNameType *entry);
extern "C" char *__cdecl strncat(char *destination,char const *source,unsigned count);
// @ref ?Unknown_005c9320@@YI_NPAUNodeNameType@@@Z=005c9320
// @ref ?Unknown_Lobby_Entry_Name_005cd0e0@@YI?AVWstring@@PAUNodeNameType@@@Z=005cd0e0
void __fastcall Unknown_0073c480()
{
    char text[256];
    strcpy(text,"L");
    for(int i=0;i<8;++i) {
        NodeNameType *entry=unknown_player_slots_a3fa98[i];
        Wstring name;
        if(Unknown_005c9320(entry)) name=Narrow_Copy_00771280(entry->Name);
        else name=Unknown_Lobby_Entry_Name_005cd0e0(entry);
        strncat(text,name.Get(),256);
        strncat(text,",",256);
    }
    unknown_chat_a72cfc->unknown_slot15(text);
}
