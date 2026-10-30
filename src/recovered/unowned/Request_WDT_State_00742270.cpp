#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern char wol_registry_key_007e6ad8[];
extern char wol_sku_name_007fdad8[];
extern char wol_wdt_debug_007fe48c[];
// @ref ?wol_registry_key_007e6ad8@@3PADA=007e6ad8
// @ref ?wol_sku_name_007fdad8@@3PADA=007fdad8
// @ref ?wol_wdt_debug_007fe48c@@3PADA=007fe48c
bool __fastcall Unknown_00742270()
{
    DWORD value=0;
    HKEY key;
    char path[256];
    char const *registry_path=wol_registry_key_007e6ad8;
    if(registry_path && strlen(registry_path)) {
        strcpy(path,registry_path);
        if(RegOpenKeyExA((HKEY)0x80000002,path,0,0x20019,&key)==0) {
            DWORD type;
            DWORD size=sizeof(value);
            RegQueryValueExA(key,wol_sku_name_007fdad8,0,&type,(BYTE *)&value,&size);
            RegCloseKey(key);
        }
    }
    unknown_b2ac5c=value & 0xff;
    if(unknown_chat_a72cfc) unknown_chat_a72cfc->unknown_slot35(value);
    if(unknown_ladder_client_a72d00) {
        Debug_Printf(wol_wdt_debug_007fe48c,unknown_wdt_address_b269ac,unknown_wdt_port_b299bc);
        unknown_ladder_client_a72d00->Request_WDT_State(unknown_wdt_address_b269ac,unknown_wdt_port_b299bc,3);
        return true;
    }
    return false;
}
