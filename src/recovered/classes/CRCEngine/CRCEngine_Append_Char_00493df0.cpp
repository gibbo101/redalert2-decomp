#include "shared/ini_class.hpp"
void CRCEngine::operator()(char value)
{
    if(Index==0) StagingBuffer.Composite=0;
    StagingBuffer.Buffer[Index++]=value;
    if(Index==4) {
        CRC=Value();
        Index=0;
    }
}
