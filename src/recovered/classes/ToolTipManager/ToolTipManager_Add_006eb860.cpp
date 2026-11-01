// bool ToolTipManager::Add(ToolTip const &tip) (0x006EB860)
// Registers a copy of the tip unless its ID is already known: the copy goes into Tips and the ID index.
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0

bool ToolTipManager::Add(ToolTip const &tip)
{
    if (!Find(tip.ID, 0)) {
        ToolTip *tooltip = new ToolTip(tip);
        if (tooltip != 0) {
            if (Tips.Add(tooltip)) {
                Index.Add_Index(tooltip->ID, tooltip);
                return true;
            }
            delete tooltip;
        }
    }
    return false;
}
