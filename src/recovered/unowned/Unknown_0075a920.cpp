#include "shared/wol_sink.hpp"
#include "shared/wdt_campaign_layout.hpp"
#include "shared/ipx_address.hpp"
#include "shared/options_dialog.hpp"
#include "shared/crt_string.hpp"
extern Wstring unknown_b2997c;
extern WolStringArray unknown_strings_b29828;
extern int unknown_b2ac2c,unknown_b2ab88;
extern long unknown_b2a8a4;
extern char wol_source_file_007fd62c[];
bool __fastcall Unknown_00514EE0();
int __fastcall Get_Performance_Profile();
void __fastcall Collect_Remote_Player_Names_0075a6c0();
void __fastcall Service_Pending_Player_Pings_0075b2d0();
// Provisional genuine getter ABI: prerequisite rename of the accepted Leaf_769670 placeholder is required before delivery.
rc_ptr<WorldDominationTour::Campaign> const &__fastcall Current_WDT_Campaign_00769670();
// @ref ?Current_WDT_Campaign_00769670@@YIABV?$rc_ptr@VCampaign@WorldDominationTour@@@@XZ=00769670
// Compiler-generated rc_ptr<Campaign> scalar destructor: original kept copy at 00726B40, independently bounded36+12NOP.
// @ref ??_G?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ?unknown_a40230@@3HA=00a40230
// @ref ?unknown_b2997c@@3VWstring@@A=00b2997c
// @ref ?unknown_strings_b29828@@3V?$WolArrayList@VWstring@@@@A=00b29828
// @ref ?unknown_b2ac2c@@3HA=00b2ac2c
// @ref ?unknown_b2ab88@@3HA=00b2ab88
// @ref ?unknown_b2a8a4@@3JA=00b2a8a4
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
extern char request_match_match_prefix_007fff4c[];
// @ref ?request_match_match_prefix_007fff4c@@3PADA=007fff4c
extern char request_match_match_wdt_prefix_007fff40[];
// @ref ?request_match_match_wdt_prefix_007fff40@@3PADA=007fff40
extern char request_match_side_zero_007fff38[];
// @ref ?request_match_side_zero_007fff38@@3PADA=007fff38
extern char request_match_side_one_007fff30[];
// @ref ?request_match_side_one_007fff30@@3PADA=007fff30
extern char request_match_territory_option_007fff28[];
// @ref ?request_match_territory_option_007fff28@@3PADA=007fff28
extern char request_match_request_match_label_007fff14[];
// @ref ?request_match_request_match_label_007fff14@@3PADA=007fff14
extern char request_match_country_option_007fff0c[];
// @ref ?request_match_country_option_007fff0c@@3PADA=007fff0c
extern char request_match_color_option_007fff04[];
// @ref ?request_match_color_option_007fff04@@3PADA=007fff04
extern char request_match_locale_option_007ffefc[];
// @ref ?request_match_locale_option_007ffefc@@3PADA=007ffefc
extern char request_match_rating_option_007ffef4[];
// @ref ?request_match_rating_option_007ffef4@@3PADA=007ffef4
extern char request_match_resolution_option_007ffeec[];
// @ref ?request_match_resolution_option_007ffeec@@3PADA=007ffeec
extern char request_match_address_option_007ffee4[];
// @ref ?request_match_address_option_007ffee4@@3PADA=007ffee4
extern char request_match_nat_option_007ffedc[];
// @ref ?request_match_nat_option_007ffedc@@3PADA=007ffedc
extern char request_match_port_option_007ffed4[];
// @ref ?request_match_port_option_007ffed4@@3PADA=007ffed4
extern char request_match_user_count_007ffea0[];
// @ref ?request_match_user_count_007ffea0@@3PADA=007ffea0

bool __fastcall Unknown_0075a920()
{
    unknown_b2997c.Release();
    void *dialog=Unknown_00735940(0x11f);
    if(dialog) Unknown_007357E0(dialog,0);
    unknown_b2ac40=0;
    Unknown_00514EE0();
    WOL::User user,owner;
    int owner_index;
    if(unknown_users_b2a728.Count<2) {
        unknown_b2ac2c=1;
        unknown_b26898=0;
        unknown_b2ab88=-1;
        unknown_b2a8a4=time(0);
        return false;
    }
    unknown_strings_b29980.Clear();
    unknown_strings_b29828.Clear();
    unknown_b26568=0;
    Collect_Remote_Player_Names_0075a6c0();
    memset(&user,0,sizeof(user));
    owner_index=-1;
    Debug_Printf(request_match_user_count_007ffea0,unknown_users_b2a728.Count);
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(user,i);
        if(user.flags&1) owner_index=i;
    }
    if(owner_index==-1) {
        unknown_b2ac2c=1;
        unknown_b26898=0;
        unknown_b2ab88=-1;
        unknown_b2a8a4=time(0);
        return false;
    }
    memset(&owner,0,sizeof(owner));
    unknown_users_b2a728.Get_Copy(owner,owner_index);
    owner.next=0;
    WolRegistryOptions registry;
    registry.Read_004ff200();
    rc_ptr<PlayerProfile> profile;
    if(registry.unknown_004ff2c0()) profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
    else profile.Set(unknown_profile_b28cc4);
    int country=profile->Country;
    Wstring match(request_match_match_prefix_007fff4c);
    Wstring side;
    if(unknown_a3d2a4==2) {
        match=request_match_match_wdt_prefix_007fff40;
        rc_ptr<WorldDominationTour::Campaign> campaign(Current_WDT_Campaign_00769670());
        if(!campaign.Get()) side=request_match_side_zero_007fff38;
        else {
            switch(campaign->PlayerFaction) {
            case 3:
                side=request_match_side_one_007fff30;
                if(country>=0 && country<=4) country=-1;
                break;
            case 2:
                side=request_match_side_zero_007fff38;
                if(country>4) country=-1;
                break;
            default:
                unknown_b2ac2c=0;
                unknown_b26898=0;
                unknown_b2ab88=-1;
                unknown_b2a8a4=time(0);
                return false;
            }
        }
        side+=request_match_territory_option_007fff28;
        side+=Wstring_From_Integer(unknown_session_a3d2a0);
    }
    Unknown_005C2C80(unknown_color_7a7368,StringTable::Load_String(request_match_request_match_label_007fff14,0,wol_source_file_007fd62c,0x6643));
    Wstring options(match);
    options+=request_match_country_option_007fff0c;
    options+=Wstring_From_Integer(country);
    options+=request_match_color_option_007fff04;
    options+=Wstring_From_Integer(profile->Color);
    Wstring nickname(unknown_wstring_b26cb8);
    nickname.To_Lower();
    if(unknown_channel_names_b293a0.Contains(nickname)) {
        int locale=0;
        int *value;
        if(unknown_channel_names_b293a0.Get_Pointer(nickname,&value) && value) locale=*value;
        options+=request_match_locale_option_007ffefc;
        options+=Wstring_From_Integer(locale);
    }
    options+=request_match_rating_option_007ffef4;
    options+=Wstring_From_Integer(Get_Performance_Profile());
    options+=request_match_resolution_option_007ffeec;
    options+=Wstring_From_Integer(unknown_8523e0);
    NetNumType net;
    NetNodeType node;
    unsigned short socket;
    unknown_address_a3fbc8.Get_Address(net,node,&socket);
    int address=*(int *)node;
    options+=request_match_address_option_007ffee4;
    options+=Wstring_From_Integer(address);
    options+=request_match_nat_option_007ffedc;
    options+=Wstring_From_Integer(unknown_identifier_a71b18.unknown_00&0xffff);
    options+=request_match_port_option_007ffed4;
    options+=Wstring_From_Integer(unknown_a40230);
    options+=side;
    unknown_chat_a72cfc->unknown_slot12(&owner,options.Get());
    unknown_b2ac2c=0;
    unknown_b26898=4;
    unknown_b2ab88=180;
    unknown_b2a8a4=time(0);
    Service_Pending_Player_Pings_0075b2d0();
    return true;
}
