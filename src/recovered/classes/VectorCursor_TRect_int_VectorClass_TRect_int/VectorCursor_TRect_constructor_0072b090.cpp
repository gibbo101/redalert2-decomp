#define VECTOR_CURSOR_REFERENCE_FORM
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/trect.hpp"
#include "shared/vector_cursor.hpp"
template<> VectorCursor<TRect<int>, VectorClass<TRect<int> > >::VectorCursor(VectorClass<TRect<int> > &vector, int index)
    : Vector(&vector), Index(index)
{
}
