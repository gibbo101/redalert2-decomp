// Voxel cache index: signed keys, lazy sorting and archive lookup.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#include "shared/unit.hpp"
// @ref ?Compare_Nodes_006d98d0@UnknownBuffer@@=006d98d0
// @ref ?Search_For_Node_006d9850@UnknownBuffer@@=006d9850
// @ref ?Is_Present_0070a350@UnknownBuffer@@=0070a350
// @ref ?Is_Archive_Same_0070a3f0@UnknownBuffer@@=0070a3f0
UnknownBuffer::NodeElement const *UnknownBuffer::Search_For_Node_006d9850(int const &id) const
    {
        if (unknown_04==0) return 0;
        if (!unknown_0c) {
            qsort(unknown_00,unknown_04,sizeof(NodeElement),Compare_Nodes_006d98d0);
            const_cast<UnknownBuffer *>(this)->unknown_10=0;
            const_cast<UnknownBuffer *>(this)->unknown_0c=true;
        }
        NodeElement target;
        target.ID=id;
        return Binary_Search(static_cast<NodeElement *>(unknown_00),unknown_04,target);
    }
