// Dynamic initializer of a second global 256x256 8-bit BSurface over a
// static 64 KB buffer (0x00716E20; registers the destructor 0x00716E80).
// Unresolved: names and use of the surface (0x00AE0C80) and its buffer
// (0x00AD0A70); see the first global for the source-file question.
#include "shared/surface.hpp"
// @ref ?unknown_buffer_ad0a70@@3PAEA=00ad0a70
// @ref ?unknown_surface_ae0c80@@3VBSurface@@A=00ae0c80
// @ref _atexit=0078298a

extern unsigned char unknown_buffer_ad0a70[256 * 256];

BSurface unknown_surface_ae0c80(256, 256, 1, unknown_buffer_ad0a70);
