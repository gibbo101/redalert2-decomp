#include "shared/blit.hpp"
void ZBuffer::Clear(unsigned short value) { Surface->Fill_Rect(Rect(0,0,Width,Height),value); }
