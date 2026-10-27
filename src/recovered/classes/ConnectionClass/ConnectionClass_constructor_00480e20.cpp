// ConnectionClass::ConnectionClass(int numsend, int numreceive, int maxlen, unsigned short magicnum, unsigned long retry_delta, unsigned long max_retries, unsigned long timeout, int extralen) (0x00480E20)
// Keeps the protocol settings and creates the packet buffer and queue.
#include "shared/connection.hpp"
// @ref ??_7ConnectionClass@@6B@=0079ddcc
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0CommBufferClass@@QAE@HHHH@Z=004800c0

ConnectionClass::ConnectionClass(int numsend, int numreceive, int maxlen, unsigned short magicnum,
    unsigned long retry_delta, unsigned long max_retries, unsigned long timeout, int extralen)
{
    MaxPacketLen = maxlen + sizeof(CommHeaderType);
    MagicNum = magicnum;
    RetryDelta = retry_delta;
    MaxRetries = max_retries;
    Timeout = timeout;
    PacketBuf = new char[MaxPacketLen];
    Queue = new CommBufferClass(numsend, numreceive, MaxPacketLen, extralen);
}
