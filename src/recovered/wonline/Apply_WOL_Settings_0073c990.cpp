#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_settings.hpp"
#include "shared/theme.hpp"
#include "shared/wol_main.hpp"
void __fastcall Apply_WOL_Settings_0073c990();
inline void Restart_Lobby_Music() { Theme.Stop(false); Theme.Queue_Song(-2); }
void __fastcall Apply_WOL_Settings_0073c990()
{
    if(unknown_chat_a72cfc) {
        unknown_chat_a72cfc->SetLangFilter(unknown_wol_lang_filter_b2a7e4);
        unknown_chat_a72cfc->SetFindPage(unknown_wol_allow_find_b2a818,unknown_wol_allow_page_b290a0);
    }
    Unknown_005cd540(0);
    bool music=unknown_wol_lob_music_b297c8!=0;
    if(music && !Theme.Still_Playing()) Restart_Lobby_Music();
    else if(music) { if(Theme.What_Is_Playing()==Theme.From_Name("INTRO")) Restart_Lobby_Music(); }
    else if(!music) Theme.Queue_Song(-3);
}
