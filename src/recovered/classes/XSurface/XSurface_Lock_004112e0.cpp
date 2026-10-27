// void *XSurface::Lock(int x, int y) (0x004112E0)
// Counts the lock; a generic surface has no memory (returns null).
// Inline member of shared/surface.hpp, emitted as a COMDAT wherever the
// vtable is needed; the linker kept the copy from the first object file
// (AbsType.cpp). This unit emits it through the BSurface globals (0x00716DA0).
#include "shared/surface.hpp"
