#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/vector_class.hpp"
class BuildingTypeClass;
// Original caller64C68E assigns RulesClass.BuildBarracks at+81C;13 call sites
// copy TypeList's+18 separately, and MapGen579F98 uses the BuildingType vector base destructor.
template class DynamicVectorClass<BuildingTypeClass *>;
