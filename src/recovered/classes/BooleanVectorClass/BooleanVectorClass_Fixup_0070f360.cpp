// BooleanVectorClass::Fixup (0x0070F360): writes Copy back to bit LastIndex and fetches bit index
// (an out-of-range index only flushes).
// @ref ??_7?$VectorClass@E@@6B@=007ae6ec
// @ref ??_G?$VectorClass@E@@UAEPAXI@Z=0070f3c0
// @ref ?Set_Bit@@YIXPAXHH@Z=0052ee40
// @ref ?Get_Bit@@YIHPBXH@Z=0052ee90
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/boolean_vector.hpp"
#include "shared/crt_memory.hpp"

void BooleanVectorClass::Fixup(int index) const
{
    if ((unsigned)index >= BitCount) {
        index = -1;
    }

    if (index != LastIndex) {
        if (LastIndex != -1) {
            Set_Bit((void *)&BitArray[0], LastIndex, Copy);
        }
        if (index != -1) {
            ((unsigned char &)Copy) = Get_Bit(&BitArray[0], index);
        }
        ((int &)LastIndex) = index;
    }
}
