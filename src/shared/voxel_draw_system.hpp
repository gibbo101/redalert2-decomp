// Voxel rendering surface API: original00717040 returns the already recovered
// BSurface at00AE0DB8. Namespace and operation follow the reference voxdrsys.h;
// original callers and complete provider establish the zero-argument ABI.
#ifndef RA2_SHARED_VOXEL_DRAW_SYSTEM_HPP
#define RA2_SHARED_VOXEL_DRAW_SYSTEM_HPP
class Surface;
class BSurface;
extern BSurface unknown_surface_ae0db8;
namespace VoxelDrawSystem {
    Surface *Get_Surface(); // original0x00717040
}
#endif
