// An interface pointer, the millisecond timer and the mixfile lists defined in the unit at 0x0040CE70 (.CRT$XCU): each definition emits its
// dynamic initializer (the inline DynamicVectorClass constructor) and the atexit destructor
// (the inline VectorClass destructor: Clear of owned storage).
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/cd.hpp"
#include "shared/milsectmr.hpp"
#include "shared/com_api.hpp"
// @ref ?unknown_com_pointer_8324b0@@3V?$CComPtr@UIUnknown@@@@A=008324b0
// @ref ?MillisecondTimer@@3VMillisecondTimerClass@@A=00837448
// @ref ??0MillisecondTimerClass@@QAE@XZ=00593530
// @ref ??1MillisecondTimerClass@@QAE@XZ=005935c0
// @ref ??_7?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@6B@=0079aa34
// @ref ??_7?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@6B@=0079aa54
// @ref ??_E?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEPAXI@Z=0040d720
// @ref ??8?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UBE_NABV0@@Z=0040d470
// @ref ?Resize@?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAE_NHPBQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d5f0
// @ref ?Clear@?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEXXZ=0040d410
// @ref ?ID@?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEHABQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d6a0
// @ref ?ID@?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEHPBQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d440
// @ref ?Fetch@?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UBEPAV?$MixFileClass@VCCFileClass@@@@H@Z=0040d460
// @ref ??_E?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEPAXI@Z=0040d6d0
// @ref ?Resize@?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAE_NHPBQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d4b0
// @ref ?Clear@?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEXXZ=0040d560
// @ref ?ID@?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEHABQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d590
// @ref ?ID@?$VectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@UAEHPBQAV?$MixFileClass@VCCFileClass@@@@@Z=0040d5d0
// @ref ?unknown_expansion_mixes_837450@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=00837450
// @ref ?unknown_mixes_837480@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=00837480
// @ref ?unknown_maps_mixes_837468@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=00837468
// @ref ?unknown_movies_mixes_8374a0@@3V?$DynamicVectorClass@PAV?$MixFileClass@VCCFileClass@@@@@@A=008374a0

// An interface pointer nothing else in the game reads; released at exit (0x008324B0; the
// interface type is unknown).
CComPtr<IUnknown> unknown_com_pointer_8324b0;

// The game's millisecond timer (0x00837448).
MillisecondTimerClass MillisecondTimer;

DynamicVectorClass<MixFileClass<CCFileClass> *> unknown_expansion_mixes_837450;
DynamicVectorClass<MixFileClass<CCFileClass> *> unknown_mixes_837480;
DynamicVectorClass<MixFileClass<CCFileClass> *> unknown_maps_mixes_837468;
DynamicVectorClass<MixFileClass<CCFileClass> *> unknown_movies_mixes_8374a0;
