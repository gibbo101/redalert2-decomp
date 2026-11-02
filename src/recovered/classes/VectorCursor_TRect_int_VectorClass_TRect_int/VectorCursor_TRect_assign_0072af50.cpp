#define VECTOR_CURSOR_REFERENCE_FORM
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/trect.hpp"
#include "shared/vector_cursor.hpp"
// @ref ??4?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@QAEAAV0@ABV0@@Z=0072af50
// @ref ??0?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@QAE@AAV?$VectorClass@V?$TRect@H@@@@H@Z=0072b090
// @ref ??_G?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEPAXI@Z=0072b0f0
// @ref ?Valid@?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UBE_NXZ=0072b0b0
// @ref ?Next@?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEAAV1@XZ=0072b8d0
// @ref ?Prev@?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEAAV1@XZ=0072b8e0
// @ref ??_7?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@6B@=007af284
// @ref ??3@YAXPAX@Z=00781d3b
typedef VectorCursor<TRect<int>, VectorClass<TRect<int> > > RectCursor;
template<> VectorCursor<TRect<int>, VectorClass<TRect<int> > >::VectorCursor(VectorClass<TRect<int> > &vector, int index);
template<> RectCursor &VectorCursor<TRect<int>, VectorClass<TRect<int> > >::operator=(RectCursor const &other)
{
    Vector = other.Vector;
    Index = other.Index;
    return *this;
}
