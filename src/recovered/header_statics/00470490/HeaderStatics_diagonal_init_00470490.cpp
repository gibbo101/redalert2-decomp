// The Cell.cpp unit expands Rect::operator- 0x0047D000 in TibSun form (Rect(Top_Left() - point, ...)) with
// Top_Left and the corner constructor inline (rect.hpp RA2_RECT_CORNER_INLINE); 0x0047D040 stays out of line.
#define RA2_RECT_CORNER_INLINE
// CellClass::Preview_Cell_Color 0x004710D0 and the tile variation helper Clear_Icon 0x004767A0 it calls,
// with the RGBClass channel accessors.
#define CELL_DECLARE_PREVIEW_CELL_COLOR
#define CELL_DECLARE_CLEAR_ICON
#define RGB_DECLARE_ACCESSORS
#define CELL_DECLARE_CELL_COLOR
#define RGB_DECLARE_BRIGHTEN
#define RA2_SHAPE_FRAME_COLOR
#define RA2_DRAW_SHAPE_OPERATIONS
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
// Header-static dynamic initializers of the unit at 0x00470490:  the
// shared/unknown_geometry.hpp constants and unknown_static_rect.hpp
// (0x00470490-0x00470676); the other
// drafts of this plan are emitted by these includes.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __CIpow=007821b0
// @ref __ftol=0077f110
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@40078000000000000000=0079a700
// @ref _unknown_geometry_angle45=00850c20
// @ref _unknown_geometry_angle60=00850be8
// @ref _unknown_geometry_angle90=00850bb0
// @ref _unknown_geometry_b=00850c38
// @ref _unknown_geometry_c=00850c28
// @ref _unknown_geometry_deg_to_rad=0079dac8
// @ref _unknown_geometry_diagonal=00850be0
// @ref _unknown_geometry_g=00850c40
// @ref _unknown_geometry_h=00850bf8
// @ref _unknown_geometry_i=00850c10
// @ref _unknown_geometry_j=00850c30
// @ref _unknown_geometry_k=00850bd8
// @ref _unknown_geometry_l=00850c00
// @ref _unknown_geometry_sixty=0079dac0
// @ref _unknown_static_rect=00850bc0
