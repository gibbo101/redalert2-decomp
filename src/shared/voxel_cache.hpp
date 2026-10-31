// Voxel cache operations used by the Techno object/shadow draw family.
#ifndef RA2_SHARED_VOXEL_CACHE_HPP
#define RA2_SHARED_VOXEL_CACHE_HPP
#include "shared/foot.hpp"
#include "shared/voxel_draw_system.hpp"
// SurfaceRegion fields follow native six-word return/copy observations.
struct SurfaceRegion { Point2D Point; Rect Bounds; };
class StaticBufferClass {
public:
    struct Entry;
    Entry *Add(Surface &surface, SurfaceRegion const &region);
    unsigned char *Buffer;
    int Capacity;
    unsigned char *Current;
};
extern StaticBufferClass unknown_voxel_static_buffer_839aa0;
extern void *unknown_cache_empty_b2b624;
#include "shared/ini_class.hpp"
// The reference cache node comparisons supply this existing algorithm's
// real operator calls; other node types keep their accepted generic provider.
template<> inline UnknownBuffer::NodeElement *__fastcall Binary_Search<UnknownBuffer::NodeElement>(UnknownBuffer::NodeElement *array,int count,UnknownBuffer::NodeElement const &target)
{
    int remaining=count;
    while (remaining>0) {
        int pivot=remaining/2;
        UnknownBuffer::NodeElement const *middle=array+pivot;
        if (target<*middle) remaining=pivot;
        else {
            if (*middle==target) return const_cast<UnknownBuffer::NodeElement *>(middle);
            array=const_cast<UnknownBuffer::NodeElement *>(middle+1);
            remaining-=pivot+1;
        }
    }
    return 0;
}

// Existing accepted search implementation stays fully visible in this real unit.
inline UnknownBuffer::NodeElement const *UnknownBuffer::Search_For_Node_006d9850(int const &id) const
    {
        if (unknown_04==0) return 0;
        if (!unknown_0c) {
            qsort(unknown_00,unknown_04,sizeof(NodeElement),Compare_Nodes_006d98d0);
            Invalidate_Archive();
            const_cast<UnknownBuffer *>(this)->unknown_0c=true;
        }
        NodeElement target;
        target.ID=id;
        return Binary_Search(static_cast<NodeElement *>(unknown_00),unknown_04,target);
    }

inline void UnknownBuffer::Invalidate_Archive() const { const_cast<UnknownBuffer *>(this)->unknown_10=0; }
inline void UnknownBuffer::Set_Archive(NodeElement const *node) const { const_cast<UnknownBuffer *>(this)->unknown_10=(int)node; }
inline bool UnknownBuffer::Is_Archive_Same_0070a3f0(int const &id) const
    {
        NodeElement const *node=reinterpret_cast<NodeElement const *>(unknown_10);
        if (node && node->ID==id) return true;
        return false;
    }

inline bool UnknownBuffer::Is_Present_0070a350(int const &id) const
    {
        if (unknown_04==0) return false;
        if (Is_Archive_Same_0070a3f0(id)) return true;
        NodeElement const *node=Search_For_Node_006d9850(id);
        if (node) {
            Set_Archive(node);
            return true;
        }
        return false;
    }

inline void * const &UnknownBuffer::operator[](int const &id) const
{
    if (Is_Present_0070a350(id)) return ((NodeElement const *)unknown_10)->Data;
    return unknown_cache_empty_b2b624;
}
inline bool UnknownBuffer::Add_Index(int const &id,void * const &data)
{
    if (unknown_04+1>unknown_08) {
        if (!Increase_Size_006d97c0(unknown_08==0 ? 10 : unknown_08)) return false;
    }
    ((NodeElement *)unknown_00)[unknown_04].ID=id;
    ((NodeElement *)unknown_00)[unknown_04].Data=data;
    ++unknown_04;
    unknown_0c=false;
    return true;
}

#endif
