#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"
#include "shared/win32_find.hpp"
// Actual original RTTI at7A5E8C names DynamicVector<_WIN32_FIND_DATAA*>.
// Canonical WIN32_FIND_DATA is the existing evidenced SDK-layout type;
// this new source does not rename or alter any accepted interface.
template class DynamicVectorClass<WIN32_FIND_DATA *>;
