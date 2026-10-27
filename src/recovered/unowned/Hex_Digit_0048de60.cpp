#include "shared/quoted_printable.hpp"
char __fastcall Hex_Digit_0048de60(int value)
{
    if(value<0 || value>15) return 0;
    if(value<10) return value+'0';
    return value+'7';
}
