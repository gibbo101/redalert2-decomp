// ToolTipIndexNode *__fastcall Binary_Search(table, count, target) (0x006EC350)
// Tiberian Sun's bsearch.h Binary_Search on the index nodes (expanded twice in Find 0x006EBBA0).
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"

ToolTipIndexNode *__fastcall Binary_Search(ToolTipIndexNode *table, int count, ToolTipIndexNode const &target)
{
    ToolTipIndexNode const *pointer = table;
    int stride = count;

    while (0 < stride) {
        int const pivot = stride / 2;
        ToolTipIndexNode const *const tryptr = pointer + pivot;
        if (target < *tryptr) {
            stride = pivot;
        } else {
            if (*tryptr == target) {
                return (ToolTipIndexNode *)tryptr;
            }
            pointer = tryptr + 1;
            stride -= pivot + 1;
        }
    }
    return 0;
}
