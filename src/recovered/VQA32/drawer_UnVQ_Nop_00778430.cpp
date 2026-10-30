// void __cdecl UnVQ_Nop(...) -- 0x00778430
// Purpose: the UnVQ decoder installed when no decoder fits the movie.
#include "shared/vqa_player.hpp"

void __cdecl UnVQ_Nop(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                      unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
{
}
