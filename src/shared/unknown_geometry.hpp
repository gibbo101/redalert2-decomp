// File-local geometry constants of an unidentified game header (each unit
// that includes it gets its own copies and dynamic initializers, e.g. the
// VQA unit 0x0071C340-0x0071C501 and the unit starting at 0x0071DC10).
// Values: a 256-unit cell's diagonal and angle constants. Names are
// hypotheses; the math helpers are the game's table-based functions.
#ifndef RA2_SHARED_UNKNOWN_GEOMETRY_HPP
#define RA2_SHARED_UNKNOWN_GEOMETRY_HPP

#include "shared/coord.hpp"

extern "C" double __cdecl pow(double x, double y);
#pragma intrinsic(pow)
double __cdecl unknown_sqrt_4ba410(double value);     // 0x004BA410
double __cdecl unknown_math_4ba520(double value);     // 0x004BA520 (table lookup)
double __cdecl unknown_math_4ba5b0(double value);     // 0x004BA5B0

static double const unknown_geometry_sixty = 60.0;
static double const unknown_geometry_deg_to_rad = 0.017453292519943295;
static double unknown_geometry_diagonal = unknown_sqrt_4ba410(pow(256.0, 2.0) * 2);
static double unknown_geometry_b = unknown_geometry_diagonal / unknown_geometry_sixty;
static double unknown_geometry_c = 1.0 / unknown_geometry_b;
static double unknown_geometry_angle45 = unknown_geometry_deg_to_rad * 45.0;
static double unknown_geometry_angle60 = unknown_geometry_deg_to_rad * 60.0;
static double unknown_geometry_angle90 = unknown_geometry_deg_to_rad * 90.0;
// A level height in leptons (ObjectClass uses it).
static int unknown_geometry_g = (int)(unknown_math_4ba520(unknown_geometry_angle90 - unknown_geometry_angle60)
                                      * unknown_geometry_diagonal * 0.5);
static double unknown_geometry_h = unknown_math_4ba5b0(unknown_geometry_g / 256.0);
static double unknown_geometry_i = unknown_math_4ba5b0((unknown_geometry_g * 2) / unknown_geometry_diagonal);
static int unknown_geometry_j = (int)(unknown_geometry_g * 4 + 0.5);
// The all-zero cell and coordinate (AbstractClass::Center_Coord returns the
// coordinate).
static Cell const unknown_geometry_k(0, 0);
static CoordStruct const unknown_geometry_l(0, 0, 0);

#endif
