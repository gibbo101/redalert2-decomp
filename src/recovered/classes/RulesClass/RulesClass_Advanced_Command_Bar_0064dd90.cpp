// RulesClass::Advanced_Command_Bar (0x0064DD90)
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _RulesSection_AdvancedCommandBar=007a90a4
// @ref _RulesSection_ButtonList=007a90ac
// @ref _RulesSection_MultiplayerAdvancedCommandBar=007a90a8
// @ref _RulesSection_None=007a90b0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_0BD@HMPB@AdvancedCommandBar?$AA@=007eeb90
// @ref ??_C@_0BO@HHCM@MultiplayerAdvancedCommandBar?$AA@=007eeb70
// @ref ??_C@_0L@DCEN@ButtonList?$AA@=007eeb64
// Lays out the advanced command bar from ButtonList= of [AdvancedCommandBar]
// ([MultiplayerAdvancedCommandBar] in multiplayer): every slot is cleared,
// then each listed command name takes the next slot.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/tab.hpp"
#include "shared/crt_tokens.hpp"

bool RulesClass::Advanced_Command_Bar(CCINIClass &ini, bool multiplayer)
{
    char const *section = multiplayer ? RulesSection_MultiplayerAdvancedCommandBar : RulesSection_AdvancedCommandBar;
    if (ini.Is_Present(section)) {
        for (int slot = 0; slot < 25; slot++) {
            TabClass::Unknown_006A05E0(slot, unknown_no_command_7f67f4);
        }
        char buffer[512];
        if (ini.Get_String(section, RulesSection_ButtonList, RulesSection_None, buffer, sizeof(buffer))) {
            int count = 0;
            int position = 0;
            for (char *token = strtok(buffer, ","); token != 0; token = strtok(0, ",")) {
                int command = TabClass::Unknown_006A0580(token);
                if (command != unknown_no_command_7f67f4) {
                    TabClass::Unknown_006A05E0(command, position);
                }
                count++;
                position++;
            }
            TabClass::Unknown_006A0670(count);
        }
        return true;
    }
    return false;
}
