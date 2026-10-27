// void ToolTipManager::Hide_Current() (0x006EBEC0)
#include "shared/tool_tip.hpp"

void ToolTipManager::Hide_Current()
{
    if (Current != 0) {
        Hide(&Record);
    }
}
