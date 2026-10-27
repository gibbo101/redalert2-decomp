// Store value into count 16-bit entries from pointer: a leading single
// entry when pointer is not 4-byte aligned, then packed pairs, then a final
// single entry. As in the original, the final entry is written only when at
// least one pair was (the tail address stays null otherwise).
#include "shared/blit.hpp"
void ABuffer::Fill_Words(unsigned short *pointer, int count, unsigned short value)
{
    if (((unsigned int)pointer & 2u) && count) {
        *pointer++=value;
        --count;
    }
    unsigned int pairs=(unsigned int)(count>>1);
    unsigned int *tail=0;
    if(pairs) {
        unsigned int packed=((unsigned int)value<<16)+(unsigned int)value;
        unsigned int *output=(unsigned int *)pointer;
        for(unsigned int remaining=pairs;remaining;--remaining) *output++=packed;
        tail=output;
    }
    if((count&1u) && tail) *(unsigned short *)tail=value;
}
