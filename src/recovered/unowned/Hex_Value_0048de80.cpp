#include "shared/quoted_printable.hpp"
int __fastcall Hex_Value_0048de80(char value)
{
    if(value<='9' && value>='0') return value-'0';
    if(value<='f' && value>='a') return value-'a'+10;
    if(value<='F' && value>='A') return value-'A'+10;
    return 0;
}
