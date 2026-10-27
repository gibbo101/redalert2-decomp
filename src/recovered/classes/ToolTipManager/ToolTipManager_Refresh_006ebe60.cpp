// void ToolTipManager::Refresh(bool update) (0x006EBE60, slot 3)
// @ref ?Update@ToolTipManager@@QAE_NXZ=006ebdb0
// @ref ?Debug_Print@ToolTipManager@@UAEXPAUToolTipRecord@@@Z=006ebe90
#include "shared/tool_tip.hpp"

void ToolTipManager::Refresh(bool update)
{
    if (update == true) {
        Update();
    }
    if (Current != 0) {
        Debug_Print(&Record);
    }
}
