// A file-local all-zero 16-byte constant from an unidentified header
// (hypothesis: a Rect), initialized dynamically after the
// shared/unknown_geometry.hpp constants in Abstract.cpp (0x0040FEF0),
// Object.cpp (0x005D22C0) and Mission.cpp (0x005944E0).
#ifndef RA2_SHARED_UNKNOWN_STATIC_RECT_HPP
#define RA2_SHARED_UNKNOWN_STATIC_RECT_HPP

#include "shared/rect.hpp"

static Rect const unknown_static_rect(0, 0, 0, 0);

#endif
