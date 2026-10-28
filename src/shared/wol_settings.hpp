// The World Online lobby switches kept in RA2.INI [WOnline] (loaded by 0x0073C7C0,
// saved by 0x0073C890); the two callees run after the load and the save.
#ifndef RA2_SHARED_WOL_SETTINGS_HPP
#define RA2_SHARED_WOL_SETTINGS_HPP

extern int unknown_wol_allow_page_b290a0;       // 0x00B290A0 AllowPage
extern int unknown_wol_allow_find_b2a818;       // 0x00B2A818 AllowFind
extern int unknown_wol_lang_filter_b2a7e4;      // 0x00B2A7E4 LangFilter
extern int unknown_wol_lob_music_b297c8;        // 0x00B297C8 LobMusic
extern int unknown_wol_show_all_b2a634;         // 0x00B2A634 ShowAll
extern int unknown_wol_display_asian_b2a804;    // 0x00B2A804 DisplayAsian
extern int unknown_wol_display_latin_b2a7e8;    // 0x00B2A7E8 DisplayLatin

void __fastcall Unknown_005CD380();             // 0x005CD380 reads one more [MultiPlayer] switch from RA2.INI
void __fastcall Unknown_005CD3A0();             // 0x005CD3A0 writes it back

void __fastcall Unknown_WOL_Load_Settings_0073C7C0();
void __fastcall Unknown_WOL_Save_Settings_0073C890();

#endif
