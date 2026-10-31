// Shared surface blitter declaration extracted unchanged from wwmouse.hpp.
// Keeps the voxel unit independent of shape_file.hpp header statics.
#ifndef RA2_SHARED_SURFACE_BLIT_HPP
#define RA2_SHARED_SURFACE_BLIT_HPP
#include "shared/surface.hpp"
void __fastcall unknown_blit_49f3a0(Surface &dest, void *convert, Surface &source, Rect const &sourcerect,
                                    RectPoint2D const &destpoint, Rect const &destclip, int unknown1, int unknown2,
                                    int unknown3, int unknown4, int unknown5, int unknown6);
#endif
