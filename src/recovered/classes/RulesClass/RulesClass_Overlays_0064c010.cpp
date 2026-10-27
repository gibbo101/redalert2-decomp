// RulesClass::Overlays (0x0064C010)
// @ref ?Find_Or_Make@OverlayTypeClass@@SIPAV1@PBD@Z=005dcf70
// @ref _RulesSection_OverlayTypes=007a908c
// @ref ??_C@_0N@CBFP@OverlayTypes?$AA@=007eebfc
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a OverlayTypeClass for every name listed in [OverlayTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/overlay_type.hpp"

bool RulesClass::Overlays(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_OverlayTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_OverlayTypes, ini.Get_Entry(RulesSection_OverlayTypes, index), "", buffer, sizeof(buffer))) {
            OverlayTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
