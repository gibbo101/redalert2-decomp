#include "shared/crc_stream.hpp"
// @ref ??RCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ?Put@Pipe@@UAEHPBXH@Z=0060eaf0
// @ref ?Get@Straw@@UAEHPAXH@Z=0069b0a0
// @ref ?CRC_Memory_00494190@@YIKPBXIK@Z=00494190
int UnknownCRCPipe::Put(void const *source,int length)
{
    Engine(source,length);
    return Pipe::Put(source,length);
}
