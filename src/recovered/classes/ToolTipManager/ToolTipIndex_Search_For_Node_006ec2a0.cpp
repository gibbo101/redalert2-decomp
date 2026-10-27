// ToolTipIndexNode const *ToolTipIndex::Search_For_Node(unsigned int const &id) const (0x006EC2A0)
// Sorts the table when needed, then binary searches it.
// @ref _qsort=00781d46
// @ref ?search_compfunc@ToolTipIndex@@SAHPBX0@Z=006ec320
#include "shared/tool_tip.hpp"

ToolTipIndexNode const *ToolTipIndex::Search_For_Node(unsigned int const &id) const
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(&IndexTable[0], IndexCount, sizeof(IndexTable[0]), search_compfunc);
        ((ToolTipIndex *)this)->Archive = 0;
        ((ToolTipIndex *)this)->IsSorted = true;
    }
    ToolTipIndexNode node;
    node.ID = id;
    return Binary_Search(IndexTable, IndexCount, node);
}
