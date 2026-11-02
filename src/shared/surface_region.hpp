// SurfaceRegion: a point and a rectangle (moved out of shared/voxel_cache.hpp so the StaticBufferClass unit
// 0x0069A180 can take one without the voxel headers). Fields follow native six-word return/copy observations.
#ifndef RA2_SHARED_SURFACE_REGION_HPP
#define RA2_SHARED_SURFACE_REGION_HPP

#include "shared/rect.hpp"

struct SurfaceRegion { Point2D Point; Rect Bounds; };

#endif
