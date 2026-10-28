#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
// Original57608F and region destructor delete an index from the RTTI-evidenced
// DynamicVectorClass<MapRegionClass *> global atA6FD28.
class MapRegionClass;
template class DynamicVectorClass<MapRegionClass *>;
