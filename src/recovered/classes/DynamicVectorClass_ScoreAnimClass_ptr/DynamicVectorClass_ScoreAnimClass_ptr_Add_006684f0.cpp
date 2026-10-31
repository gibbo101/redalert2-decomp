// DynamicVectorClass<ScoreAnimClass *>::Add (0x006684F0).
// Layout and behaviour: shared/vector_class.hpp. The Score unit's out-of-line copy
// (ScoreClass::Anims; called six times from 0x006647F2-0x00664ECF).
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"

class ScoreAnimClass;

template class DynamicVectorClass<ScoreAnimClass *>;
