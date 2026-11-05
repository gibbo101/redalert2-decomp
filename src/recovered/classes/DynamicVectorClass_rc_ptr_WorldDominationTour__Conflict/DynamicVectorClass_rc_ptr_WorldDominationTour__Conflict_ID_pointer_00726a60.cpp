// Pointer index in the campaign conflict list (0x00726A60; vtable007AF004 slot5).
// Use the recovered eight-byte rc_ptr class shared by the complete campaign unit.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"
#include "shared/reference_counted.hpp"
namespace WorldDominationTour { class Conflict; }
template class DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict> >;
