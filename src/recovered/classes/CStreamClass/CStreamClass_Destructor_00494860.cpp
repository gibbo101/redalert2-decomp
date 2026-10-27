#include "shared/cstream.hpp"
CStreamClass::~CStreamClass()
{
    if(Stream!=0) Unlink_Stream(0);
    delete [] (char *)unknown_20;
    unknown_20=0;
    delete [] (char *)unknown_18;
    unknown_18=0;
    delete [] (char *)unknown_1c;
    unknown_1c=0;
}
