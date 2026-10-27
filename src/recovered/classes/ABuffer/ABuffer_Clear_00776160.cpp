#include "shared/blit.hpp"
void ABuffer::Clear(unsigned short color) { Surface->Fill_Rect(Rect(0,0,Width,Height),color); }
