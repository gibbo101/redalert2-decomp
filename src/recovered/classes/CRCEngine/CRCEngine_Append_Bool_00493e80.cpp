#include "shared/ini_class.hpp"
void CRCEngine::operator()(bool value)
{
    if(Index==0) StagingBuffer.Composite=0;
    StagingBuffer.Buffer[Index++]=value ? 1 : 0;
    if(Index==4) {
        CRC=Value();
        Index=0;
    }
}
