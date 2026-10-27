// DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption>>::ID_pointer (0x00727BC0; DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption>> vtable 0x007af08c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// rc_ptr<WorldDominationTour::GameOption> is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class GameOption;
};

template <class A0>
struct rc_ptr {
    int unknown[2];
};

template class DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption> >;
