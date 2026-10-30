// RGBClass::RGBClass(unsigned char red, unsigned char green, unsigned char blue) (0x00432D70)
// Inline constructor of shared/rgb_class.hpp, emitted as a COMDAT wherever a caller keeps it out of
// line; the linker kept the first object file's copy. Init.CPP emits it through Init_Game's inline
// Bootstrap, whose palette conversions call it out of line once the inline budget is spent.
#include "shared/rgb_class.hpp"
