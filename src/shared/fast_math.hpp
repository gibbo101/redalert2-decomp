// Table-driven trigonometry and square root (0x004BA410-0x004BA6B1): each
// function takes a double and returns a float. The tables and scale factors
// are filled at startup (0x004BA6F0 builds the square-root mantissa table).
// shared/unknown_geometry.hpp declares 0x004BA410/0x004BA520/0x004BA5B0 as
// unknown_sqrt_4ba410 / unknown_math_4ba520 / unknown_math_4ba5b0 returning
// double; these are the same functions (proposal: use these declarations).
#ifndef RA2_SHARED_FAST_MATH_HPP
#define RA2_SHARED_FAST_MATH_HPP

// The float square root itself (TibSun fastmath::sqrtf; __stdcall, see its source).
float __stdcall Fast_Sqrt_Float_004BA830(float value); // 0x004BA830
float __cdecl Fast_Sqrt(double value);              // 0x004BA410
float __cdecl Fast_Sin(double angle);               // 0x004BA480
float __cdecl Fast_Cos(double angle);               // 0x004BA4D0
float __cdecl Fast_Sin_4096(double angle);          // 0x004BA520 (4096-entry table; name hypothesis)
float __cdecl Fast_Acos(double value);              // 0x004BA550
float __cdecl Fast_Asin(double value);              // 0x004BA580
float __cdecl Fast_Atan(double value);              // 0x004BA5B0
float __cdecl Fast_Atan2(double y, double x);       // 0x004BA600

extern float unknown_sin_scale_7d8048;              // table steps per radian (Fast_Sin)
extern float unknown_cos_scale_7d804c;              // the same for Fast_Cos
extern float unknown_atan_step_817df8;              // tangent step of the arctangent table
extern float unknown_sin_table_801dc4[];            // sine, 0x2000 entries (+0x800 for cosine)
extern float unknown_sin_table_80fde4[];            // 0x1000 entries
extern float unknown_acos_table_80bdd4[];           // indexed backwards from here
extern float unknown_atan_table_813df4[];           // 0x1001 entries
extern unsigned int unknown_sqrt_table_817dfc[];    // mantissa square roots, 0x2000 entries

#endif
