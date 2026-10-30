// Voxel cache index: signed keys, lazy sorting and archive lookup.
#include "shared/unit.hpp"
// @ref ?Compare_Nodes_006d98d0@UnknownBuffer@@=006d98d0
// @ref ?Search_For_Node_006d9850@UnknownBuffer@@=006d9850
// @ref ?Is_Present_0070a350@UnknownBuffer@@=0070a350
// @ref ?Is_Archive_Same_0070a3f0@UnknownBuffer@@=0070a3f0
bool UnknownBuffer::Is_Archive_Same_0070a3f0(int const &id) const
    {
        NodeElement const *node=reinterpret_cast<NodeElement const *>(unknown_10);
        if (node && node->ID==id) return true;
        return false;
    }
