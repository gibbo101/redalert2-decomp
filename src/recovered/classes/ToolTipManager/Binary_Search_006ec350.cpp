// ToolTipIndexNode *__fastcall Binary_Search(table, count, target) (0x006EC350)
#include "shared/tool_tip.hpp"

ToolTipIndexNode *__fastcall Binary_Search(ToolTipIndexNode *table, int count, ToolTipIndexNode const &target)
{
    int remaining = count;
    if (remaining > 0) {
        while (remaining > 0) {
            int half = remaining / 2;
            ToolTipIndexNode *node = &table[half];
            if (node->ID > target.ID) {
                remaining = half;
            } else if (node->ID == target.ID) {
                return node;
            } else {
                table = node + 1;
                remaining = remaining - 1 - half;
            }
        }
    }
    return 0;
}
