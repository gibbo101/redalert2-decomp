// ColorScheme::ColorScheme() (0x00663930; Tiberian Sun scheme.cpp): a blank scheme with no name
// or converter yet that takes its place in ColorSchemes.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/color_scheme.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

ColorScheme::ColorScheme() :
    Name(0),
    BaseColor(0, 0, 0),
    Converter(0),
    unknown_0x310(1)
{
    ColorSchemes.Add(this);
    Index = ColorSchemes.Count();
}
