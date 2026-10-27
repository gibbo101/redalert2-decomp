// DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict>>::ID_pointer (0x00726A60; DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict>> vtable 0x007af004 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// rc_ptr<WorldDominationTour::Conflict> is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Conflict;
};

template <class A0>
struct rc_ptr {
    int unknown[2];
};

template class DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict> >;
