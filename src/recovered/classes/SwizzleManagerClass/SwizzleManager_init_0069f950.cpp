// SwizzleManager (0x00ABD868) and its dynamic initializer (0x0069F950, _$E4), which expands the
// constructor with an out-of-line VectorClass<SwizzlePointerClass> constructor call per table; the
// atexit destructor is _$E2 (0x0069F9D0).
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/swizzle.hpp"

// @ref ??_7?$DynamicVectorClass@USwizzlePointerClass@@@@6B@=007ac35c
// @ref ??_7?$VectorClass@USwizzlePointerClass@@@@6B@=007ac37c

// Template members this unit emits; the kept copies are the explicit instantiations accepted at
// their own addresses.
// @ref ?Clear@?$DynamicVectorClass@USwizzlePointerClass@@@@UAEXXZ=0069fdd0
// @ref ?ID@?$DynamicVectorClass@USwizzlePointerClass@@@@UAEHPBUSwizzlePointerClass@@@Z=0069fe00
// @ref ?Fetch@?$VectorClass@USwizzlePointerClass@@@@UBE?AUSwizzlePointerClass@@H@Z=0069fe20
// @ref ??8?$VectorClass@USwizzlePointerClass@@@@UBE_NABV0@@Z=0069fe40
// @ref ?Resize@?$VectorClass@USwizzlePointerClass@@@@UAE_NHPBUSwizzlePointerClass@@@Z=0069fe80
// @ref ?Clear@?$VectorClass@USwizzlePointerClass@@@@UAEXXZ=0069ff70
// @ref ?ID@?$VectorClass@USwizzlePointerClass@@@@UAEHABUSwizzlePointerClass@@@Z=0069ffa0
// @ref ?ID@?$VectorClass@USwizzlePointerClass@@@@UAEHPBUSwizzlePointerClass@@@Z=0069ffe0
// @ref ?Resize@?$DynamicVectorClass@USwizzlePointerClass@@@@UAE_NHPBUSwizzlePointerClass@@@Z=006a0000
// @ref ?ID@?$DynamicVectorClass@USwizzlePointerClass@@@@UAEHABUSwizzlePointerClass@@@Z=006a0100

SwizzleManagerClass SwizzleManager;
