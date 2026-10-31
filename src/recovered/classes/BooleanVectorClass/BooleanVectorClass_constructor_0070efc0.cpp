// BooleanVectorClass::BooleanVectorClass(unsigned size, unsigned char *array) (0x0070EFC0).
// @ref ??_7?$VectorClass@E@@6B@=007ae6ec
// @ref ??_G?$VectorClass@E@@UAEPAXI@Z=0070f3c0
// @ref ?Set_Bit@@YIXPAXHH@Z=0052ee40
// @ref ?Get_Bit@@YIHPBXH@Z=0052ee90
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/boolean_vector.hpp"
#include "shared/crt_memory.hpp"

BooleanVectorClass::BooleanVectorClass(unsigned size, unsigned char *array) :
    BitCount(size),
    Copy(false),
    LastIndex(-1),
    BitArray(0, 0)
{
    BitArray.Resize((size + (8 - 1)) / 8, array);
}
