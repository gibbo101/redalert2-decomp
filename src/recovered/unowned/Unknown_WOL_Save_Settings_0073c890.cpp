// void __fastcall Unknown_WOL_Save_Settings_0073C890() (0x0073C890)
// Writes the seven World Online lobby switches to [WOnline] of RA2.INI, saves the INI
// file and then runs 0x005CD3A0.
// @ref ??_C@_07DNIH@ShowAll?$AA@=007fd684
// @ref ??_C@_07GKMN@WOnline?$AA@=007fd6b0
// @ref ??_C@_08KADD@LobMusic?$AA@=007fd68c
// @ref ??_C@_09BOHF@AllowFind?$AA@=007fd6a4
// @ref ??_C@_09NGE@AllowPage?$AA@=007fd6b8
// @ref ??_C@_0L@IHPO@LangFilter?$AA@=007fd698
// @ref ??_C@_0N@MPJB@DisplayAsian?$AA@=007fd674
// @ref ??_C@_0N@OPEJ@DisplayLatin?$AA@=007fd664
// @ref ?Unknown_005CD3A0@@YIXXZ=005cd3a0
// @ref ?unknown_wol_allow_find_b2a818@@3HA=00b2a818
// @ref ?unknown_wol_allow_page_b290a0@@3HA=00b290a0
// @ref ?unknown_wol_display_asian_b2a804@@3HA=00b2a804
// @ref ?unknown_wol_display_latin_b2a7e8@@3HA=00b2a7e8
// @ref ?unknown_wol_lang_filter_b2a7e4@@3HA=00b2a7e4
// @ref ?unknown_wol_lob_music_b297c8@@3HA=00b297c8
// @ref ?unknown_wol_show_all_b2a634@@3HA=00b2a634
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
// @ref ?Save@CCINIClass@@QAEHAAVFileClass@@_N@Z=004698f0
// @ref ?unknown_ini_839740@@3VCCINIClass@@A=00839740
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
#include "shared/raw_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/wol_settings.hpp"

void __fastcall Unknown_WOL_Save_Settings_0073C890()
{
    RawFileClass file("RA2.INI");
    unknown_ini_839740.Put_Int("WOnline", "AllowPage", unknown_wol_allow_page_b290a0);
    unknown_ini_839740.Put_Int("WOnline", "AllowFind", unknown_wol_allow_find_b2a818);
    unknown_ini_839740.Put_Int("WOnline", "LangFilter", unknown_wol_lang_filter_b2a7e4);
    unknown_ini_839740.Put_Int("WOnline", "LobMusic", unknown_wol_lob_music_b297c8);
    unknown_ini_839740.Put_Int("WOnline", "ShowAll", unknown_wol_show_all_b2a634);
    unknown_ini_839740.Put_Int("WOnline", "DisplayAsian", unknown_wol_display_asian_b2a804);
    unknown_ini_839740.Put_Int("WOnline", "DisplayLatin", unknown_wol_display_latin_b2a7e8);
    unknown_ini_839740.Save(file, false);
    Unknown_005CD3A0();
}
