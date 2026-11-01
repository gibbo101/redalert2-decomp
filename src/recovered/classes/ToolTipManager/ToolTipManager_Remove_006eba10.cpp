// void ToolTipManager::Remove(unsigned int id) (0x006EBA10)
// Unregisters and deletes the tip with this ID (hiding it first when it is the one shown).
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _qsort=00781d46
// @ref ?search_compfunc@ToolTipIndex@@SAHPBX0@Z=006ec320
// @ref ?x@?1???AToolTipIndex@@QBEABQAVToolTip@@ABI@Z@4PAV2@A=00b2b620

void ToolTipManager::Remove(unsigned int id)
{
    if (Index.Is_Present(id)) {
        ToolTip *tooltip = Index[id];
        if (Current == tooltip) {
            Hide_Current();
        }
        Index.Remove_Index(tooltip->ID);
        Tips.Delete(tooltip);
        if (tooltip != 0) {
            delete tooltip;
        }
    }
}
