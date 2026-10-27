// ColorScheme::~ColorScheme() -- 0x00663BB0
// Purpose: frees the name (+0x304, from _strdup), deletes the converter
// (+0x30C) and removes the scheme from ColorSchemes (0x00AB6EF8).
// Assumptions: ColorScheme as shared/ccini_extra.hpp and text_print.hpp
// declare it (no vtable); the destructor is a hypothesis for this
// clean-up (no direct callers).
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref _free=007825e8

extern "C" void __cdecl free(void *block);

class ConvertClass {
public:
    virtual ~ConvertClass();
};

class ColorScheme {
public:
    ~ColorScheme();

    unsigned char unknown_0x000[0x304];
    char *Name;                         // +0x304
    unsigned char unknown_0x308[0x04];
    ConvertClass *Converter;            // +0x30C
};
extern DynamicVectorClass<ColorScheme *> ColorSchemes;      // 0x00AB6EF8

ColorScheme::~ColorScheme()
{
    if (Name != 0) {
        free(Name);
    }
    Name = 0;
    delete Converter;
    Converter = 0;
    ColorSchemes.Delete(this);
}
