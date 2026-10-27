// void ToolTipManager::Hide(ToolTipRecord *record) (0x006EBD90, slot 2)
// Clears the shown tip (the argument is the member record).
#include "shared/tool_tip.hpp"

void ToolTipManager::Hide(ToolTipRecord *record)
{
    Record.unknown_00 = 0;
    Record.unknown_04 = 0;
    Record.unknown_08 = 0;
    Record.unknown_0c = 0;
    Current = 0;
}
