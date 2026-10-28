// VectorClass<TeamTypeClass const *>::operator= (0x006C0930).
// Called at 0x006BF12F, where a VectorClass<TeamTypeClass const *> (vtable
// 0x007A2EE4, named by its RTTI) is copy-constructed inline.
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class TeamTypeClass;

template class VectorClass<TeamTypeClass const *>;
