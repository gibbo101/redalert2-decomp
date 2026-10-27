// void CommBufferClass::Configure_Debug(int offset, int size, int names, int namestart, int namecount) (0x00480AB0)
#include "shared/comm_buffer.hpp"

void CommBufferClass::Configure_Debug(int offset, int size, int names, int namestart, int namecount)
{
    DebugOffset = offset;
    DebugSize = size;
    DebugNames = names;
    DebugNameStart = namestart;
    DebugNameCount = namecount;
}
