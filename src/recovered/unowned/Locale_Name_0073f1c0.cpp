#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
extern char wol_locale_label_prefix_7fd808[];
extern char wol_source_file_007fd62c[];
// @ref ?wol_locale_label_prefix_7fd808@@3PADA=007fd808
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ??H@YI?AVWstring@@PBDABV0@@Z=0076f6b0
WideString __fastcall Locale_Name_0073f1c0(int locale)
{
    Wstring label=wol_locale_label_prefix_7fd808+Wstring_From_Integer(locale,2);
    WideString text(StringTable::Load_String(label.Get(),0,wol_source_file_007fd62c,0xa54));
    // The original tests this bound before copying the same localized value on either path.
    if(locale<37) return text;
    else return text;
}
