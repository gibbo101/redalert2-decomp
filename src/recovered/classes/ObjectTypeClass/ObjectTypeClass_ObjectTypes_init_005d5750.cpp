// Dynamic initializer of ObjectTypeClass::ObjectTypes (0x005D5750, _$E) and its guarded atexit
// destructor (0x005D5790), emitted by the definition below: an empty DynamicVectorClass (growth
// step 10). The destructor's guard is bit 0 of 0x00A72FD9.
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/object_type.hpp"
// @ref ?ObjectTypes@ObjectTypeClass@@2V?$DynamicVectorClass@PAVObjectTypeClass@@@@A=00a72f90

DynamicVectorClass<ObjectTypeClass *> ObjectTypeClass::ObjectTypes;
// @ref _$E42=005d5790
// @ref _$S43=00a72fd9
// @ref ??_7?$VectorClass@PAVObjectTypeClass@@@@6B@=007a76ac
// @ref ??_7?$DynamicVectorClass@PAVObjectTypeClass@@@@6B@=007a768c
