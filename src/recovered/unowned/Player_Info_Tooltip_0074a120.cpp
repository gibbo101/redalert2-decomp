#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
// @ref _swprintf=00783764
extern wchar_t wol_player_tooltip_b290a4[];
// @ref ?wol_player_tooltip_b290a4@@3PAGA=00b290a4
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
extern char tooltip_label_7fd814[];
// @ref ?tooltip_label_7fd814@@3PADA=007fd814
extern char tooltip_label_7fd828[];
// @ref ?tooltip_label_7fd828@@3PADA=007fd828
extern char tooltip_label_7feb84[];
// @ref ?tooltip_label_7feb84@@3PADA=007feb84
extern char tooltip_label_7feb68[];
// @ref ?tooltip_label_7feb68@@3PADA=007feb68
extern char tooltip_label_7feb4c[];
// @ref ?tooltip_label_7feb4c@@3PADA=007feb4c
extern char tooltip_label_7feb30[];
// @ref ?tooltip_label_7feb30@@3PADA=007feb30
extern char tooltip_label_7feb10[];
// @ref ?tooltip_label_7feb10@@3PADA=007feb10
extern char tooltip_label_7feaf4[];
// @ref ?tooltip_label_7feaf4@@3PADA=007feaf4
wchar_t *__fastcall Player_Info_Tooltip_0074a120(wchar_t const *name)
{
    Wstring player_name;
    WOL::Ladder player_ladder;
    memset(&player_ladder,0,sizeof(player_ladder));
    player_name.Set(Unknown_006FA120(name));
    player_name.To_Lower();
    bool player_found;
    WolLadderCache *cache=unknown_ladder_cache_b2ac24;
    if(cache && cache->Count) {
        WolLadderCache::Node *node=cache->Buckets[cache->Key_Hash_00767550(player_name)];
        if(node) {
            while(node && !(node->Key==player_name)) node=node->Next;
            if(node) {
                WOL::Ladder *value=&node->Value;
                if(value) player_ladder=*value;
                player_found=true;
                goto player_lookup_done;
            }
        }
    }
    player_found=false;
player_lookup_done:
    {
    WOL::Ladder squad_ladder;
    memset(&squad_ladder,0,sizeof(squad_ladder));
    Wstring squad_abbreviation;
    WOL::User user;
    for(int index=0;index<unknown_users_b2a728.Count;++index) {
        unknown_users_b2a728.Get_Copy(user,index);
        if(strcmp(user.name,Unknown_006FA120(name))==0) break;
    }
    bool has_squad=false;
    bool squad_found=false;
    if(strlen(user.unknown_2e)!=0) {
        has_squad=true;
        squad_abbreviation.Set(user.unknown_57);
        squad_abbreviation.To_Lower();
        if(unknown_ladder_b296f8.Count) {
            WolLadderCache::Node *node=unknown_ladder_b296f8.Buckets[unknown_ladder_b296f8.Key_Hash(squad_abbreviation)];
            if(node) {
                while(node && !(node->Key==squad_abbreviation)) node=node->Next;
                if(node) {
                    WOL::Ladder *value=&node->Value;
                    if(value) squad_ladder=*value;
                    squad_found=true;
                }
            }
        }
    }
    if(player_found) {
        if(has_squad) {
            if(squad_found) {
                wchar_t *squad_name=Unknown_006FA180(user.unknown_2e);
                swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feb84,0,wol_source_file_007fd62c,0x36ce),StringTable::Load_String(tooltip_label_7fd814,0,wol_source_file_007fd62c,0x36ce),player_ladder.unknown_1c,squad_name,squad_ladder.unknown_1c);
            } else {
                wchar_t *squad_name=Unknown_006FA180(user.unknown_2e);
                swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feb68,0,wol_source_file_007fd62c,0x36d2),StringTable::Load_String(tooltip_label_7fd814,0,wol_source_file_007fd62c,0x36d2),player_ladder.unknown_1c,squad_name);
            }
        } else {
            swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feb4c,0,wol_source_file_007fd62c,0x36d6),StringTable::Load_String(tooltip_label_7fd814,0,wol_source_file_007fd62c,0x36d6),player_ladder.unknown_1c);
        }
    } else {
        if(has_squad) {
            if(squad_found) {
                wchar_t *squad_name=Unknown_006FA180(user.unknown_2e);
                swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feb30,0,wol_source_file_007fd62c,0x36dc),StringTable::Load_String(tooltip_label_7fd828,0,wol_source_file_007fd62c,0x36dc),squad_name,squad_ladder.unknown_1c);
            } else {
                wchar_t *squad_name=Unknown_006FA180(user.unknown_2e);
                swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feb10,0,wol_source_file_007fd62c,0x36e0),StringTable::Load_String(tooltip_label_7fd828,0,wol_source_file_007fd62c,0x36e0),squad_name);
            }
        } else {
            swprintf(wol_player_tooltip_b290a4,StringTable::Load_String(tooltip_label_7feaf4,0,wol_source_file_007fd62c,0x36e4),StringTable::Load_String(tooltip_label_7fd828,0,wol_source_file_007fd62c,0x36e4));
        }
    }
    }
    return wol_player_tooltip_b290a4;
}
