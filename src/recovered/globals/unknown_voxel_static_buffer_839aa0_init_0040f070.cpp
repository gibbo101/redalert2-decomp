// The voxel draw cache's static buffer (0x00839AA0, 4,000,000 bytes): its definition emits the
// dynamic initializer 0x0040F070 and the atexit destructor 0x0040F090.
#define STATIC_BUFFER_DECLARE_LIFETIME
#include "shared/static_buffer.hpp"
// @ref ?unknown_voxel_static_buffer_839aa0@@3VStaticBufferClass@@A=00839aa0
// @ref ??0StaticBufferClass@@QAE@H@Z=0069a1a0
// @ref ??1StaticBufferClass@@QAE@XZ=0069a1c0

StaticBufferClass unknown_voxel_static_buffer_839aa0(4000000);
