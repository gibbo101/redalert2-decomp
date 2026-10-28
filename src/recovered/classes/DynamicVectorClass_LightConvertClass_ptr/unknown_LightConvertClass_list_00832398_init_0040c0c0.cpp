// The light converter list's unit (0x0040C0C0-0x0040C49F): its only global,
// unknown_LightConvertClass_list_00832398 (declared in shared/isometric_tile_type.hpp),
// with its initializer (0x0040C0C0) and atexit destructor (0x0040C100); the
// list's template members and vtables (0x0079A85C, 0x0079A87C) follow as this
// unit's COMDAT copies (0x0040C140-0x0040C3D0 accepted as standalone members;
// the two deleting destructors 0x0040C400/0x0040C450 are claimed here).
// @ref ??8?$VectorClass@PAVLightConvertClass@@@@UBE_NABV0@@Z=0040c1a0
// @ref ??_7?$DynamicVectorClass@PAVLightConvertClass@@@@6B@=0079a85c
// @ref ??_7?$VectorClass@PAVLightConvertClass@@@@6B@=0079a87c
// @ref ?Clear@?$DynamicVectorClass@PAVLightConvertClass@@@@UAEXXZ=0040c140
// @ref ?Clear@?$VectorClass@PAVLightConvertClass@@@@UAEXXZ=0040c290
// @ref ?Fetch@?$VectorClass@PAVLightConvertClass@@@@UBEPAVLightConvertClass@@H@Z=0040c190
// @ref ?ID@?$DynamicVectorClass@PAVLightConvertClass@@@@UAEHABQAVLightConvertClass@@@Z=0040c3d0
// @ref ?ID@?$DynamicVectorClass@PAVLightConvertClass@@@@UAEHPBQAVLightConvertClass@@@Z=0040c170
// @ref ?ID@?$VectorClass@PAVLightConvertClass@@@@UAEHABQAVLightConvertClass@@@Z=0040c2c0
// @ref ?ID@?$VectorClass@PAVLightConvertClass@@@@UAEHPBQAVLightConvertClass@@@Z=0040c300
// @ref ?Resize@?$DynamicVectorClass@PAVLightConvertClass@@@@UAE_NHPBQAVLightConvertClass@@@Z=0040c320
// @ref ?Resize@?$VectorClass@PAVLightConvertClass@@@@UAE_NHPBQAVLightConvertClass@@@Z=0040c1e0
// @ref ?unknown_LightConvertClass_list_00832398@@3V?$DynamicVectorClass@PAVLightConvertClass@@@@A=00832398
// @ref _atexit=0078298a
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class LightConvertClass;

DynamicVectorClass<LightConvertClass *> unknown_LightConvertClass_list_00832398;
