#include "shared/blit.hpp"
ZBuffer::~ZBuffer()
{
    delete Surface;
    Surface = 0;
}
