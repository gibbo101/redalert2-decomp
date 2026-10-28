// void __fastcall Unknown_WOL_Load_Settings_0073C7C0() (0x0073C7C0)
// Reads the seven World Online lobby switches from [WOnline] of RA2.INI (default 1) and
// then runs 0x005CD380.
// @ref ??_C@_07DNIH@ShowAll?$AA@=007fd684
// @ref ??_C@_07GKMN@WOnline?$AA@=007fd6b0
// @ref ??_C@_08KADD@LobMusic?$AA@=007fd68c
// @ref ??_C@_09BOHF@AllowFind?$AA@=007fd6a4
// @ref ??_C@_09NGE@AllowPage?$AA@=007fd6b8
// @ref ??_C@_0L@IHPO@LangFilter?$AA@=007fd698
// @ref ??_C@_0N@MPJB@DisplayAsian?$AA@=007fd674
// @ref ??_C@_0N@OPEJ@DisplayLatin?$AA@=007fd664
// @ref ?Unknown_005CD380@@YIXXZ=005cd380
// @ref ?unknown_wol_allow_find_b2a818@@3HA=00b2a818
// @ref ?unknown_wol_allow_page_b290a0@@3HA=00b290a0
// @ref ?unknown_wol_display_asian_b2a804@@3HA=00b2a804
// @ref ?unknown_wol_display_latin_b2a7e8@@3HA=00b2a7e8
// @ref ?unknown_wol_lang_filter_b2a7e4@@3HA=00b2a7e4
// @ref ?unknown_wol_lob_music_b297c8@@3HA=00b297c8
// @ref ?unknown_wol_show_all_b2a634@@3HA=00b2a634
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ?unknown_ini_839740@@3VCCINIClass@@A=00839740
#include "shared/ccini_class.hpp"
#include "shared/wol_settings.hpp"

void __fastcall Unknown_WOL_Load_Settings_0073C7C0()
{
    unknown_wol_allow_page_b290a0 = unknown_ini_839740.Get_Int("WOnline", "AllowPage", 1);
    unknown_wol_allow_find_b2a818 = unknown_ini_839740.Get_Int("WOnline", "AllowFind", 1);
    unknown_wol_lang_filter_b2a7e4 = unknown_ini_839740.Get_Int("WOnline", "LangFilter", 1);
    unknown_wol_lob_music_b297c8 = unknown_ini_839740.Get_Int("WOnline", "LobMusic", 1);
    unknown_wol_show_all_b2a634 = unknown_ini_839740.Get_Int("WOnline", "ShowAll", 1);
    unknown_wol_display_asian_b2a804 = unknown_ini_839740.Get_Int("WOnline", "DisplayAsian", 1);
    unknown_wol_display_latin_b2a7e8 = unknown_ini_839740.Get_Int("WOnline", "DisplayLatin", 1);
    Unknown_005CD380();
}
