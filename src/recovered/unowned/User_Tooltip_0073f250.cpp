#include "shared/wol_sink.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
WideString __fastcall operator+(unsigned short const *left,WideString const &right);
WideString __fastcall Locale_Name_0073f1c0(int locale);
extern unsigned short wol_user_separator_7fd838[];
extern unsigned short wol_profile_separator_7fd820[];
extern unsigned short wol_rank_space_7d64f4[];
extern char wol_rank_label_7fd814[];
extern char wol_unranked_label_7fd828[];
extern char wol_source_file_007fd62c[];
// @ref ?Locale_Name_0073f1c0@@YI?AVWideString@@H@Z=0073f1c0
// @ref ?wol_user_separator_7fd838@@3PAGA=007fd838
// @ref ?wol_profile_separator_7fd820@@3PAGA=007fd820
// @ref ?wol_rank_space_7d64f4@@3PAGA=007d64f4
// @ref ?wol_rank_label_7fd814@@3PADA=007fd814
// @ref ?wol_unranked_label_7fd828@@3PADA=007fd828
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ??H@YI?AVWideString@@PBGABV0@@Z=00771380
// @ref ?unknown_number_text_7710c0@@YI?AVWideString@@H@Z=007710c0
WideString __fastcall User_Tooltip_0073f250(WOL::User const &user)
{
    Wstring name(user.name);
    WideString text=Wstring_To_Wide(name)+wol_user_separator_7fd838;
    name.To_Lower();
    WOL::Ladder ladder;
    memset(&ladder,0,sizeof(ladder));
    if(unknown_ladder_cache_b2ac24 && unknown_ladder_cache_b2ac24->Get_Copy(ladder,name)) {
        text+=WideString(StringTable::Load_String(wol_rank_label_7fd814,0,wol_source_file_007fd62c,0xa70))+WideString(wol_rank_space_7d64f4)+unknown_number_text_7710c0(ladder.unknown_1c);
    } else {
        text+=StringTable::Load_String(wol_unranked_label_7fd828,0,wol_source_file_007fd62c,0xa72);
    }
    Wstring profile(user.unknown_2e);
    if(profile.Length()==0) profile=user.unknown_57;
    if(profile.Length()>0) text+=wol_profile_separator_7fd820+Wstring_To_Wide(profile);
    if(unknown_channel_names_b293a0.Contains(name)) {
        int *locale=0;
        if(unknown_chat_a72cfc && unknown_channel_names_b293a0.Get_Pointer(name,&locale) && locale && *locale) {
            text+=wol_user_separator_7fd838+Locale_Name_0073f1c0(*locale);
        }
    }
    return text;
}
