#include "shared/coord.hpp"
// Copies a sentinel-terminated list of cells, bounded by the requested capacity.
// The original also writes output[-1] when capacity is nonpositive.
void __fastcall Copy_Cell_List_00482e10(Cell const *input,int capacity,Cell *output)
{
    if (input && output) {
        for (;capacity>0;--capacity) {
            *output=*input;
            if (output->X==0x7fff && output->Y==0x7fff) return;
            ++output;
            ++input;
        }
        output[-1]=Cell(0x7fff,0x7fff);
    }
}
