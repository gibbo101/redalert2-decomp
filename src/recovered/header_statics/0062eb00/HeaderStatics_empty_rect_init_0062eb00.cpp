// Rect corner point operators are inline where Render_Radar 0x00633210 expands them.
#define RA2_RECT_POINT_INLINE
#define RA2_RECT_MINUS_INLINE
#define RA2_RADAR_RENDER_VIEW
// RadarClass +0x1238 as three members (Compute_Background 0x00630B70).
#define RA2_RADAR_BACKGROUND_MEMBERS
// Existing RGB accessors are used by Radar Init_For_House in this unit.
#define RGB_DECLARE_ACCESSORS
// Header-static dynamic initializers of the unit at 0x0062EB00: the shape_file.hpp empty rect and the
// shared/unknown_geometry.hpp constants (0x0062EB00-0x0062ECE1); the other
// drafts of this plan are emitted by these includes.
#include "shared/shape_file.hpp"
#include "shared/unknown_geometry.hpp"
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
// @ref _unknown_empty_rect=00ab6320
// @ref _unknown_geometry_angle45=00ab6448
// @ref _unknown_geometry_angle60=00ab6358
// @ref _unknown_geometry_angle90=00ab6310
// @ref _unknown_geometry_b=00ab6460
// @ref _unknown_geometry_c=00ab6450
// @ref _unknown_geometry_deg_to_rad=007a8688
// @ref _unknown_geometry_diagonal=00ab6348
// @ref _unknown_geometry_g=00ab649c
// @ref _unknown_geometry_h=00ab6360
// @ref _unknown_geometry_i=00ab63e0
// @ref _unknown_geometry_j=00ab6458
// @ref _unknown_geometry_k=00ab6330
// @ref _unknown_geometry_l=00ab6370
// @ref _unknown_geometry_sixty=007a8680
