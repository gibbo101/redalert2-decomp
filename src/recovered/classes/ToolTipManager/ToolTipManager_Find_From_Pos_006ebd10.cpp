// ToolTip *ToolTipManager::Find(POINT const *point) (0x006EBD10; Tiberian Sun's Find_From_Pos)
// The registered tip whose area contains the point, or 0. No caller keeps this copy: Process_Message
// expands it.
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"

ToolTip *ToolTipManager::Find(POINT const *point)
{
    for (int index = 0; index < Tips.Count(); index++) {
        Rect const *region = &Tips[index]->Region;
        if (point->x >= region->X && point->x <= region->X + region->Width
            && point->y >= region->Y && point->y <= region->Y + region->Height) {
            return Tips[index];
        }
    }
    return 0;
}
