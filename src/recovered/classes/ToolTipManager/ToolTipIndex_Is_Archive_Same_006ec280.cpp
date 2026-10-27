// bool ToolTipIndex::Is_Archive_Same(unsigned int const &id) const (0x006EC280)
#include "shared/tool_tip.hpp"

bool ToolTipIndex::Is_Archive_Same(unsigned int const &id) const
{
    if (Archive != 0 && Archive->ID == id) {
        return true;
    }
    return false;
}
