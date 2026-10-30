#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"
extern char wol_registry_key_007e6ad8[];
extern char wol_sku_name_007fdad8[];
extern bool wol_initialized_b2ac81;
extern HANDLE wol_wait_events_b264f8[18];
void __fastcall Reset_WOL_Globals_0073e8d0();
int __fastcall Startup_Chat_00741300(HINSTANCE instance);
// @ref ?wol_registry_key_007e6ad8@@3PADA=007e6ad8
// @ref ?wol_sku_name_007fdad8@@3PADA=007fdad8
// @ref ?wol_initialized_b2ac81@@3_NA=00b2ac81
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?Reset_WOL_Globals_0073e8d0@@YIXXZ=0073e8d0
// @ref ?Startup_Chat_00741300@@YIHPAX@Z=00741300
// @ref ?ProgramInstance@@3PAXA=00b26180
int __fastcall Unknown_00742390()
{
    if(wol_initialized_b2ac81) return 1;
    wol_initialized_b2ac81=true;
    Init_Lobby_Entries_005c86e0();
    Clear_Slot_Lists_005c8a70();
    Unknown_Reset_Slots_005c8a90();
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
    value &= 0xff;
    unknown_b2ac5c=value;
    unknown_protocol_7fd370=value+0x2100;
    Reset_WOL_Globals_0073e8d0();
    unknown_b2abd8=true;
    for(int i=0;i<18;++i) wol_wait_events_b264f8[i]=CreateEventA(0,false,false,0);
    return Startup_Chat_00741300(ProgramInstance);
}
