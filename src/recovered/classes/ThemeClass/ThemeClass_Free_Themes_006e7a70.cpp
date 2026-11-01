// void ThemeClass::Unknown_006E7A70() (0x006E7A70)
// Frees every theme record, then fades out, waits for and destroys the stream.
#define THEME_CONTROL_RECORD
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#endif
#ifndef VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ?unknown_sample_407fe0@@YIXPAX@Z=00407fe0
// @ref ?unknown_sample_408010@@YIXPAX@Z=00408010
// @ref ?unknown_sample_4079c0@@YIXPAX@Z=004079c0

void __fastcall unknown_stop_sample_407e60(void *sample);
void __fastcall unknown_sample_407fe0(void *sample);
void __fastcall unknown_sample_408010(void *sample);
void __fastcall unknown_sample_4079c0(void *sample);

void ThemeClass::Unknown_006E7A70()
{
    while (Themes.Count() > 0) {
        delete Themes[0];
        Themes.Delete(0);
    }
    if (Sample != 0) {
        unknown_sample_407fe0(Sample);
        unknown_sample_408010(Sample);
        unknown_stop_sample_407e60(Sample);
        unknown_sample_4079c0(Sample);
        Sample = 0;
    }
}
