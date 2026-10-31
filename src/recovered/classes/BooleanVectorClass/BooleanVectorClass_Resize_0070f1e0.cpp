// BooleanVectorClass::Resize (0x0070F1E0): new elements start false; zero clears the vector.
// @ref ??_7?$VectorClass@E@@6B@=007ae6ec
// @ref ??_G?$VectorClass@E@@UAEPAXI@Z=0070f3c0
// @ref ?Set_Bit@@YIXPAXHH@Z=0052ee40
// @ref ?Get_Bit@@YIHPBXH@Z=0052ee90
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/boolean_vector.hpp"
#include "shared/crt_memory.hpp"

int BooleanVectorClass::Resize(unsigned size)
{
    Fixup();

    if (size > 0) {
        unsigned oldsize = BitCount;
        int success = BitArray.Resize((size + (8 - 1)) / 8);
        BitCount = size;
        if (success && oldsize < size) {
            for (unsigned index = oldsize; index < size; index++) {
                (*this)[index] = 0;
            }
        }
        return success;
    }

    Clear();
    return true;
}
