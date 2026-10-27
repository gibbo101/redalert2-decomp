#include "shared/facing.hpp"
char FacingClass::Is_Turning_Negative() const { if (Is_Rotating()) return (short)(Desired - Start) < 0; return 0; }
