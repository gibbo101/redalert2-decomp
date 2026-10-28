// The colour scheme unit's global list, ColorSchemes (0x00AB6EF8): its
// initializer (0x00663610) and atexit destructor (0x00663650). The list's
// vtables and template members are the copies at 0x007A7B98/0x007A7BB8 and
// 0x00604CD0-0x006055F0 (another unit's, kept by the linker).
// @ref ??8?$VectorClass@PAVColorScheme@@@@UBE_NABV0@@Z=00604dc0
// @ref ??_7?$DynamicVectorClass@PAVColorScheme@@@@6B@=007a7b98
// @ref ??_7?$VectorClass@PAVColorScheme@@@@6B@=007a7bb8
// @ref ??_G?$DynamicVectorClass@PAVColorScheme@@@@UAEPAXI@Z=006055f0
// @ref ??_G?$VectorClass@PAVColorScheme@@@@UAEPAXI@Z=006055a0
// @ref ?Clear@?$DynamicVectorClass@PAVColorScheme@@@@UAEXXZ=00604cd0
// @ref ?Clear@?$VectorClass@PAVColorScheme@@@@UAEXXZ=00604eb0
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Fetch@?$VectorClass@PAVColorScheme@@@@UBEPAVColorScheme@@H@Z=00604d20
// @ref ?ID@?$DynamicVectorClass@PAVColorScheme@@@@UAEHABQAVColorScheme@@@Z=00604ff0
// @ref ?ID@?$DynamicVectorClass@PAVColorScheme@@@@UAEHPBQAVColorScheme@@@Z=00604d00
// @ref ?ID@?$VectorClass@PAVColorScheme@@@@UAEHABQAVColorScheme@@@Z=00604ee0
// @ref ?ID@?$VectorClass@PAVColorScheme@@@@UAEHPBQAVColorScheme@@@Z=00604f20
// @ref ?Resize@?$DynamicVectorClass@PAVColorScheme@@@@UAE_NHPBQAVColorScheme@@@Z=00604f40
// @ref ?Resize@?$VectorClass@PAVColorScheme@@@@UAE_NHPBQAVColorScheme@@@Z=00604e00
// @ref _atexit=0078298a
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/color_scheme.hpp"

DynamicVectorClass<ColorScheme *> ColorSchemes;
