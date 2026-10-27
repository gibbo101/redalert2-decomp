// void CCToolTip::Refresh(bool update) (0x0046E230, slot 3)
// Remembers the flag and refreshes the base with its opposite.
#include "shared/tool_tip.hpp"
// @ref ?Refresh@ToolTipManager@@UAEX_N@Z=006ebe60

void CCToolTip::Refresh(bool update)
{
    unknown_260 = update;
    ToolTipManager::Refresh(update == false);
}
