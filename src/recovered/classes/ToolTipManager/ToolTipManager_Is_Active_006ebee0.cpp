// bool ToolTipManager::Is_Active() const (0x006EBEE0)
#include "shared/tool_tip.hpp"

bool ToolTipManager::Is_Active() const
{
    return Current != 0;
}
