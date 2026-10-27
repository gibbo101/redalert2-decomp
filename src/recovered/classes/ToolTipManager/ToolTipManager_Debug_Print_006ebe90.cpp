// void ToolTipManager::Debug_Print(ToolTipRecord *record) (0x006EBE90, slot 4)
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0N@KBPP@ToolTip?3?5?$CFs?6?$AA@=007f85b0
#include "shared/tool_tip.hpp"

void ToolTipManager::Debug_Print(ToolTipRecord *record)
{
    Debug_Printf("ToolTip: %s\n", record->Text);
}
