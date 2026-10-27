// VectorClass<HashObject<HashString, SchemeNode *>>::Resize (0x006058A0).
// Layout and behaviour: shared/vector_class.hpp.
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??0HashString@@QAE@ABV0@@Z=004e1180
// @ref ??8@YI_NABVHashString@@0@Z=004e1290
// @ref ??9@YI_NABVHashString@@0@Z=004e12a0
// @ref ??0HashString@@QAE@XZ=004e1130
// @ref ??4HashString@@QAEAAV0@ABV0@@Z=004e11c0
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"
#include "shared/hash_string.hpp"


template class VectorClass<HashObject<HashString, SchemeNode *> >;
