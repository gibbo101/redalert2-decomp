#include "shared/facing.hpp"
void FacingClass::Set_ROT(int rate) { if (rate >= 127) rate = 127; ROT = (unsigned short)((unsigned char)rate << 8); }
