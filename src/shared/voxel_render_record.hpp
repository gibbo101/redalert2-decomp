// The voxel draw system's object records (TibSun VoxelRenderStruct; 0x88 bytes): the 64 at 0x00AE0DE8,
// constructed by the unit at 0x00716EE0 and filled by VoxelDrawSystem::Prep_For_Object (0x007174C0).
#ifndef RA2_SHARED_VOXEL_RENDER_RECORD_HPP
#define RA2_SHARED_VOXEL_RENDER_RECORD_HPP

#include "shared/vector3.hpp"

class UnknownPairFirst;

// A voxel object record: the library, section and frame, the corner nearest the viewer, the transformed
// bounds and the eight transformed box corners.
struct UnknownVoxelRecord88 {
    UnknownPairFirst *Library;          // +0x00
    int Section;                        // +0x04
    int Frame;                          // +0x08
    int AnchorCorner;                   // +0x0C
    Vector3 MinBounds;                  // +0x10
    Vector3 MaxBounds;                  // +0x1C
    Vector3 Points[8];                  // +0x28
};

extern UnknownVoxelRecord88 unknown_records_ae0de8[64];     // 0x00AE0DE8

#endif
