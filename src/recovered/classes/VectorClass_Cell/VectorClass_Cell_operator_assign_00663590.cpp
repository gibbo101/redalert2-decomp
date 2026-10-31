// VectorClass<Cell>::operator=(VectorClass<Cell> const &) (0x00663590).
// Replaces the contents with an owned copy (shared/vector_class.hpp); the copy kept out of
// line in the Scenario unit (Multiplayer_Start_Waypoints 0x0065FFF0 calls it).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"
#include "shared/coord.hpp"

template class VectorClass<Cell>;
