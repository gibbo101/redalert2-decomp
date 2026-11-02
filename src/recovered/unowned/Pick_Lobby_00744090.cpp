// @ref ??0MixFileClass@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl wcscmp(wchar_t const *,wchar_t const *);
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned);
extern "C" unsigned __cdecl wcslen(wchar_t const *);
extern "C" wchar_t *__cdecl _wcsdup(wchar_t const *);
extern "C" long __cdecl atol(char const *);
rc_ptr<WDTState> const &Get_New_WDT_State_00769510();
void __fastcall Widen_Text_006fa0c0(wchar_t *,char const *,int);
extern PKey lobby_fast_key_00839010;
extern wchar_t *lobby_territory_name_00b28cc8;
extern char lobby_prefix_007fd358[],wdt_mix_007fe6dc[],wdt_map_ini_007fc34c[],wdt_territory_format_007fe6cc[];
extern char wdt_north_america_007fe6bc[],wdt_europe_007fe6b4[],wdt_name_key_007ce2a4[],wdt_default_name_007fe6a8[];
// @ref ?Get_New_WDT_State_00769510@@YAABV?$rc_ptr@VWDTState@@@@XZ=00769510
// @ref ?Widen_Text_006fa0c0@@YIXPAGPBDH@Z=006fa0c0
// @ref __wcsdup=00797033
// @ref _wcscmp=007837d3
// @ref _wcsncmp=007846cc
// @ref _wcslen=00783605
// @ref _atol=00782d72
// @ref ?lobby_fast_key_00839010@@3VPKey@@A=00839010
// @ref ?lobby_territory_name_00b28cc8@@3PAGA=00b28cc8
// @ref ?lobby_prefix_007fd358@@3PADA=007fd358
// @ref ?wdt_mix_007fe6dc@@3PADA=007fe6dc
// @ref ?wdt_map_ini_007fc34c@@3PADA=007fc34c
// @ref ?wdt_territory_format_007fe6cc@@3PADA=007fe6cc
// @ref ?wdt_north_america_007fe6bc@@3PADA=007fe6bc
// @ref ?wdt_europe_007fe6b4@@3PADA=007fe6b4
// @ref ?wdt_name_key_007ce2a4@@3PADA=007ce2a4
// @ref ?wdt_default_name_007fe6a8@@3PADA=007fe6a8
int __fastcall Pick_Lobby_00744090(bool require_room)
{
    int count=unknown_lobbies_b26c88.Count;
    WOL::Channel channel;
    memset(&channel,0,sizeof(channel));
    char section[32],entry[32],fallback[32],name[32];
    wchar_t territory[32];
    if(unknown_session_a3d298.Type==4 && *(int*)(unknown_session_a3d298.unknown_08+4)==2) {
        memset(section,0,sizeof(section));
        // Original clears 32 bytes of the widened-name storage before filling it.
        memset(territory,0,32);
        memset(entry,0,sizeof(entry));
        memset(fallback,0,sizeof(fallback));
        MixFileClass *archive=new MixFileClass(wdt_mix_007fe6dc,&lobby_fast_key_00839010);
        INIClass ini;
        CCFileClass file(wdt_map_ini_007fc34c);
        ini.Load(file,false);
        sprintf(entry,wdt_territory_format_007fe6cc,*(int*)unknown_session_a3d298.unknown_08);
        strcpy(fallback,entry);
        if(Get_New_WDT_State_00769510()->unknown_14==0)
            ini.Get_String(wdt_north_america_007fe6bc,entry,fallback,section,sizeof(section));
        else
            ini.Get_String(wdt_europe_007fe6b4,entry,fallback,section,sizeof(section));
        ini.Get_String(section,wdt_name_key_007ce2a4,wdt_default_name_007fe6a8,name,sizeof(name));
        Widen_Text_006fa0c0(territory,name,-1);
        lobby_territory_name_00b28cc8=_wcsdup(territory);
        delete archive;
    }
    Wstring lobby_name=Wstring(lobby_prefix_007fd358)+Wstring_From_Integer(unknown_b2abec,1);
    int i;
    for(i=0;i<count;++i) {
        unknown_lobbies_b26c88.Get(channel,i);
        if(unknown_session_a3d298.Type==4 && *(int*)(unknown_session_a3d298.unknown_08+4)==2) {
            if(wcscmp((wchar_t const*)unknown_lobby_names_b26c94[i],territory)!=0) continue;
            if(!require_room || (int)channel.currentUsers<=25) return i;
        }
        Wstring channel_name(channel.name);
        if(channel_name==lobby_name) {
            if(!require_room || (int)channel.currentUsers<=25) return i;
        }
    }
    int best=-1;
    unsigned int smallest=10000;
    for(i=0;i<count;++i) {
        unknown_lobbies_b26c88.Get(channel,i);
        if(unknown_session_a3d298.Type==4 && *(int*)(unknown_session_a3d298.unknown_08+4)==2) {
            if(wcsncmp((wchar_t const*)unknown_lobby_names_b26c94[i],territory,wcslen(territory))!=0) continue;
            if(!require_room || (int)channel.currentUsers<=25) {
                unknown_b2abec=atol(channel.name+strlen(lobby_prefix_007fd358));
                return i;
            }
            if(channel.currentUsers<smallest) { best=i;smallest=channel.currentUsers; }
        }
        if(strncmp(channel.name,lobby_prefix_007fd358,strlen(lobby_prefix_007fd358))==0) {
            if(!require_room || (int)channel.currentUsers<=25) {
                unknown_b2abec=atol(channel.name+strlen(lobby_prefix_007fd358));
                return i;
            }
            if(channel.currentUsers<smallest) { best=i;smallest=channel.currentUsers; }
        }
    }
    if(best!=-1) {
        unknown_lobbies_b26c88.Get(channel,best);
        unknown_b2abec=atol(channel.name+strlen(lobby_prefix_007fd358));
    }
    return best;
}
