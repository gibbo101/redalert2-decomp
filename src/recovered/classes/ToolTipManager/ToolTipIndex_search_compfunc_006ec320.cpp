// int __cdecl ToolTipIndex::search_compfunc(void const *left, void const *right) (0x006EC320)
// qsort comparator: orders records by ID (signed).
#include "shared/tool_tip.hpp"

int __cdecl ToolTipIndex::search_compfunc(void const *left, void const *right)
{
    if (*(int const *)left == *(int const *)right) {
        return 0;
    }
    if (*(int const *)left < *(int const *)right) {
        return -1;
    }
    return 1;
}
