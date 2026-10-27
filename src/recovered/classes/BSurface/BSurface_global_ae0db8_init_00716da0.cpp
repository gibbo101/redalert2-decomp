// Dynamic initializer of a global 256x256 8-bit BSurface over a static
// 64 KB buffer (0x00716DA0; registers the destructor 0x00716E00 with atexit).
// Unresolved: the source file (between Unit.CPP and the WDT files; next to
// DynamicVectorClass<VoxClass *>, probably a voxel renderer), the names and
// use of the surface (0x00AE0DB8) and of its buffer (0x00AE3408).
#include "shared/surface.hpp"
// @ref ?unknown_buffer_ae3408@@3PAEA=00ae3408
// @ref ?unknown_surface_ae0db8@@3VBSurface@@A=00ae0db8
// @ref _atexit=0078298a

extern unsigned char unknown_buffer_ae3408[256 * 256];

BSurface unknown_surface_ae0db8(256, 256, 1, unknown_buffer_ae3408);
