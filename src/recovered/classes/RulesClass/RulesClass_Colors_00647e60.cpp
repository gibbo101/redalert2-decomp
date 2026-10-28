// RulesClass::Colors (0x00647E60)
// @ref ?unknown_add_color_603a60@@YIXPBDABVHSVClass@@@Z=00603a60
// @ref ?unknown_find_or_make_palette@@YIHPBDABVHSVClass@@PAX2H@Z=00663ca0
// @ref ?unknown_object_838a10@@3PADA=00838a10
// @ref _RulesSection_Colors=007a9054
// @ref ??_C@_06ILJB@Colors?$AA@=007eeca4
// Each [Colors] entry names an HSV colour; a colour scheme is made for it with
// two keys (1 and 0x35). The helpers' names are placeholders.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/hsv_class.hpp"
#include "shared/anim.hpp"

// 0x00603A60: registers the named colour (an unidentified list at 0x00A76414).
void __fastcall unknown_add_color_603a60(char const *name, HSVClass const &color);
// 0x00663CA0: the index of the colour scheme named `name` with `key`, made when missing.
int __fastcall unknown_find_or_make_palette(char const *name, HSVClass const &color, void *arg3, void *arg4, int key);
extern char unknown_object_838a10[];        // 0x00838A10 (type unknown)

bool RulesClass::Colors(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_Colors)) {
        int count = ini.Entry_Count(RulesSection_Colors);
        for (int index = 0; index < count; index++) {
            char const *entry = ini.Get_Entry(RulesSection_Colors, index);
            HSVClass color = ini.Get_HSV(RulesSection_Colors, entry, HSVClass(0, 0, 0));
            unknown_add_color_603a60(entry, color);
            unknown_find_or_make_palette(entry, color, unknown_object_838a10, &unknown_palette_837e10, 1);
            unknown_find_or_make_palette(entry, color, unknown_object_838a10, &unknown_palette_837e10, 0x35);
        }
        return true;
    }
    return false;
}
