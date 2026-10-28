// Header-static dynamic initializers of the unit at 0x006EC3A0 and the
// unit's twelve AbstractClass lists; the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class AbstractClass;

// The unit's list of AbstractClass objects (0x00AC0D60; name is a hypothesis).
DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d60;
// The unit's other eleven object lists, in initializer order (0x006EC610-
// 0x006ECB50: each an initializer and an atexit destructor; every vtable
// store is DynamicVectorClass<AbstractClass *> 0x007A177C). Names are hypotheses.
DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0; // 0x00AC0CB0 (objects and types)
DynamicVectorClass<AbstractClass *> unknown_objects_ac0c58; // 0x00AC0C58
DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d48; // 0x00AC0D48 (tags and triggers)
DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0bf8; // 0x00AC0BF8 (TechnoClass +0x108 holders, bullets)
DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0c80; // 0x00AC0C80 (buildings and houses)
DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98; // 0x00AC0C98 (triggers, tags, events, actions)
DynamicVectorClass<AbstractClass *> unknown_objects_ac0c30; // 0x00AC0C30
DynamicVectorClass<AbstractClass *> unknown_list_ac0c18; // 0x00AC0C18 (foot objects and neurons)
DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0d08; // 0x00AC0D08 (technos, supers)
DynamicVectorClass<AbstractClass *> unknown_objects_ac0d30; // 0x00AC0D30
DynamicVectorClass<AbstractClass *> unknown_objects_ac0cd8; // 0x00AC0CD8
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVAbstractClass@@@@UBE_NABV0@@Z=004cdfe0
// @ref ??_7?$DynamicVectorClass@PAVAbstractClass@@@@6B@=007a177c
// @ref ??_7?$VectorClass@PAVAbstractClass@@@@6B@=007a179c
// @ref ??_G?$DynamicVectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf30
// @ref ??_G?$VectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf90
// @ref ?Clear@?$DynamicVectorClass@PAVAbstractClass@@@@UAEXXZ=004cde30
// @ref ?Clear@?$VectorClass@PAVAbstractClass@@@@UAEXXZ=004ce0d0
// @ref ?Fetch@?$VectorClass@PAVAbstractClass@@@@UBEPAVAbstractClass@@H@Z=004cde80
// @ref ?ID@?$DynamicVectorClass@PAVAbstractClass@@@@UAEHABQAVAbstractClass@@@Z=004ce260
// @ref ?ID@?$DynamicVectorClass@PAVAbstractClass@@@@UAEHPBQAVAbstractClass@@@Z=004cde60
// @ref ?ID@?$VectorClass@PAVAbstractClass@@@@UAEHABQAVAbstractClass@@@Z=004ce100
// @ref ?ID@?$VectorClass@PAVAbstractClass@@@@UAEHPBQAVAbstractClass@@@Z=004ce140
// @ref ?Resize@?$DynamicVectorClass@PAVAbstractClass@@@@UAE_NHPBQAVAbstractClass@@@Z=004ce160
// @ref ?Resize@?$VectorClass@PAVAbstractClass@@@@UAE_NHPBQAVAbstractClass@@@Z=004ce020
// @ref ?unknown_AbstractClass_list_00ac0d60@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d60
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E41=006ec5d0
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?unknown_objects_ac0c58@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c58
// @ref ?unknown_AbstractClass_list_00ac0d48@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d48
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8
// @ref ?unknown_abstracts_ac0c80@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c80
// @ref ?unknown_AbstractClass_list_00ac0c98@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c98
// @ref ?unknown_objects_ac0c30@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c30
// @ref ?unknown_list_ac0c18@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c18
// @ref ?unknown_abstracts_ac0d08@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d08
// @ref ?unknown_objects_ac0d30@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d30
// @ref ?unknown_objects_ac0cd8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cd8
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
// @ref _atexit=0078298a
// @ref _unknown_geometry_angle45=00ac0d20
// @ref _unknown_geometry_angle60=00ac0cc8
// @ref _unknown_geometry_angle90=00ac0c10
// @ref _unknown_geometry_b=00ac0d80
// @ref _unknown_geometry_c=00ac0d28
// @ref _unknown_geometry_deg_to_rad=007ad998
// @ref _unknown_geometry_diagonal=00ac0c78
// @ref _unknown_geometry_g=00ac0d88
// @ref _unknown_geometry_h=00ac0cd0
// @ref _unknown_geometry_i=00ac0d00
// @ref _unknown_geometry_j=00ac0d78
// @ref _unknown_geometry_k=00ac0c70
// @ref _unknown_geometry_l=00ac0cf0
// @ref _unknown_geometry_sixty=007ad990
// @ref _unknown_static_rect=00ac0c48
