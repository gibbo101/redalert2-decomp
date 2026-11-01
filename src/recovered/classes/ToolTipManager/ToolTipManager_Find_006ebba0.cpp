// bool ToolTipManager::Find(unsigned int id, ToolTip *tooltip) (0x006EBBA0; Tiberian Sun's Find)
// The tip registered under id exists; when tooltip is not 0 the tip is copied there. No caller keeps
// this copy: Add expands it.
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"
// @ref ?x@?1???AToolTipIndex@@QBEABQAVToolTip@@ABI@Z@4PAV2@A=00b2b620

bool ToolTipManager::Find(unsigned int id, ToolTip *tooltip)
{
    if (!Index.Is_Present(id)) {
        return false;
    }
    if (tooltip != 0) {
        *tooltip = *Index[id];
    }
    return true;
}
