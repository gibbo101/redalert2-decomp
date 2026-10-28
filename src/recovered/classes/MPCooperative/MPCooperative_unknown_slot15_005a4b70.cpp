// void MPCooperative::unknown_slot15(HWND list, DynamicVectorClass<MultiMission *> const *maps, MultiMission *selected) -- 0x005A4B70
// Fills the campaign list: makes the score screen and the campaign on first use, loads every
// campaign record, adds "<n>. <name>" for each campaign whose first map is in maps (item data: the
// map), then the saved-campaign row when there is a save, and selects the first row.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
// @ref _sprintf=007820f4
// @ref __stricmp=00781f20
// @ref _swprintf=00783764
// @ref ??0?$VectorClass@PAG@@QAE@IPBQAG@Z=0052ed90
// @ref ??_7?$DynamicVectorClass@PAG@@6B@=007a524c
// @ref ??_7?$VectorClass@PAG@@6B@=007a526c
// @ref ?Clear@?$VectorClass@PAG@@UAEXXZ=0052e880
// @ref ?Fetch@?$VectorClass@PAG@@UBEPAGH@Z=0052e720
// @ref ?ID@?$DynamicVectorClass@PAG@@UAEHPBQAG@Z=0052e700
// @ref ?Set_Names@CoopCampaignClass@@QAEXPBG0@Z=0048e190
// @ref ??0CampaignScoreClass@@QAE@XZ=00465bf0
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
// @ref ??_C@_04OANC@?4MAP?$AA@=007e375c
// @ref ??_C@_06HIDC@?$CFs?4MAP?$AA@=007e3794
// @ref ??_C@_0BC@IPCP@TXT_COOP_USE_SAVE?$AA@=007e3748
// @ref ??_C@_0BP@DFDM@?$EA?$EA?$EA?$EA?5Could?5not?5find?5?$CFs?5for?5?$CFs?6?$AA@=007e3764
// @ref ??_C@_1O@FBCE@?$AA?$CF?$AAd?$AA?4?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e3784
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/campaign_score.hpp"
#include "shared/multi_mission.hpp"
#include "shared/string_table.hpp"
#include "shared/abstract_type.hpp"
#include "shared/debug_printf.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"

void MPCooperative::unknown_slot15(HWND list, DynamicVectorClass<MultiMission *> const *maps, MultiMission *selected)
{
    unknown_04 = true;
    if (unknown_score_54 == 0) {
        unknown_score_54 = new CampaignScoreClass();
    }
    SendMessageA(list, 0x184, 0, 0);
    unknown_4d = false;
    if (unknown_campaign_44 == 0) {
        if (unknown_players_a3fa7c.Count() == 2) {
            unknown_campaign_44 = new CoopCampaignClass(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
        }
    } else if (unknown_players_a3fa7c.Count() != 2) {
        unknown_campaign_44->Set_Names(unknown_empty_wide_839d4c, unknown_empty_wide_839d4c);
    }
    if (unknown_campaigns_328.Count() == 0) {
        int records;
        unknown_campaigns_40->Get_Count_00490C90(&records);
        for (int r = 0; r < records; r++) {
            CoopCampaignClass *campaign = new CoopCampaignClass();
            campaign->Load_Campaign_0048f590(r);
            unknown_campaigns_328.Add(campaign);
        }
    }
    DynamicVectorClass<wchar_t *> names;
    unknown_campaigns_40->Copy_Names(names);
    int count = names.Length();
    int i;
    for (i = 0; i < count; i++) {
        if (names[i] != 0) {
            char *map;
            unknown_campaigns_328[i]->Get_Map_Name_0048fb40(&map, -1);
            int map_count = maps->Count();
            char name[260];
            MultiMission *found = 0;
            sprintf(name, "%s.MAP", map);
            for (int k = 0; k < map_count; k++) {
                if (found != 0) {
                    break;
                }
                char const *scenario = (*maps)[k]->unknown_58;
                if (_stricmp(scenario, name) == 0) {
                    found = (*maps)[k];
                }
            }
            if (found != 0) {
                wchar_t text[260];
                swprintf(text, L"%d. %s", i + 1, names[i]);
                SendMessageA(list, 0x4CD, 0, (LPARAM)text);
                SendMessageA(list, 0x19A, i, (LPARAM)found);
            } else {
                Debug_Printf("@@@@ Could not find %s for %s\n", name, names[i]);
            }
            delete names[i];
        }
    }
    if (unknown_campaign_44 != 0 && unknown_campaign_44->Has_Saved_Campaign_0048fbf0() && !unknown_4d) {
        char name[260];
        unknown_campaign_44->Saved_Map_Is_Undefined_0048fe70(name);
        strcat(name, ".MAP");
        int map_count = maps->Count();
        MultiMission *found = 0;
        for (int k = 0; k < map_count; k++) {
            if (found != 0) {
                break;
            }
            char const *scenario = (*maps)[k]->unknown_58;
            if (_stricmp(scenario, name) == 0) {
                found = (*maps)[k];
            }
        }
        if (found != 0) {
            SendMessageA(list, 0x4CD, 0, (LPARAM)StringTable::Load_String("TXT_COOP_USE_SAVE", 0, "D:\\Ra2\\MPCoop.cpp", 0x528));
            SendMessageA(list, 0x19A, i, (LPARAM)found);
            unknown_4d = true;
        }
    }
    SendMessageA(list, 0x186, 0, 0);
}
