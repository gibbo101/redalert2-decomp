// bool DynamicVectorClass<ZoneConnectionClass>::Resize(int newsize, ZoneConnectionClass const *array)
// (0x0056B330, vtable 0x007A59F8 slot 2). The template instance alone; the
// element constructor's Cell members expand through the charged Cell
// constructor, whose budget runs out at To (0x0042AD30 out of line).
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??0Cell@@QAE@HH@Z=0042ad30
// @ref ??0ZoneConnectionClass@@QAE@XZ=0056b460
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"
#include "shared/map_elements.hpp"

template class DynamicVectorClass<ZoneConnectionClass >;
