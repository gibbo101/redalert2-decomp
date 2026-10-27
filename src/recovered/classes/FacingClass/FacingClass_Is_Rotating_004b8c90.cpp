#include "shared/facing.hpp"
bool FacingClass::Is_Rotating() const { return ROT > 0 && Timer.Value() != 0; }
