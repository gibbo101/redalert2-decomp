// @ref ??0?$HashObject@VHashString@@PAVSchemeNode@@@@QAE@ABVHashString@@ABQAVSchemeNode@@@Z=00605d80
// @ref ??0?$DynamicVectorClass@VHSVClass@@@@QAE@IPBVHSVClass@@@Z=006051f0
#define RA2_HASH_STRING_UNIT
// Resolves the palette name to its cached list of colour schemes.
#include "shared/palette_name.hpp"
#include "shared/scheme_table.hpp"

void *__fastcall PaletteName::Load()
{
    SchemeTable *table = Scheme_Table();
    DynamicVectorClass<ColorScheme *> *schemes = table->Find_Schemes(Buffer);
    if (schemes != 0)
        return schemes;
    unknown_scheme_table_a76414->Add_Node(Buffer);
    return unknown_scheme_table_a76414->Find_Schemes(Buffer);
}
