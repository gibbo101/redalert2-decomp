// BooleanVectorClass::operator= (0x0070F0C0): stores the fetched copy back, then copies member-wise.
// @ref ??_7?$VectorClass@E@@6B@=007ae6ec
// @ref ??_G?$VectorClass@E@@UAEPAXI@Z=0070f3c0
// @ref ?Set_Bit@@YIXPAXHH@Z=0052ee40
// @ref ?Get_Bit@@YIHPBXH@Z=0052ee90
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/boolean_vector.hpp"
#include "shared/crt_memory.hpp"

BooleanVectorClass &BooleanVectorClass::operator=(BooleanVectorClass const &vector)
{
    Fixup();
    Copy = vector.Copy;
    LastIndex = vector.LastIndex;
    BitArray = vector.BitArray;
    BitCount = vector.BitCount;
    return *this;
}
