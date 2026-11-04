// WOL ArrayList<int>::setEmpty 00766060: retains storage and resets the entry count.
#define RA2_WOL_INT_ARRAY_SET_EMPTY
#include "shared/wol_sink.hpp"
void WolIntArray::Set_Empty()
{
    Count=0;
}
