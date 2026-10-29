// NullModemClass::NullModemClass(int numsend, int numreceive, int maxlen, unsigned short magicnum) (0x005CFFC0)
#include "shared/null_modem.hpp"
// @ref ??_7NullModemClass@@6B@=007a7414

NullModemClass::NullModemClass(int numsend, int numreceive, int maxlen, unsigned short magicnum) : ConnManClass()
{
    PortHandle = -1;
    Connection = 0;
    NumSend = numsend;
    NumReceive = numreceive;
    MaxLen = maxlen;
    MagicNum = magicnum;
    RXBuf = 0;
    BuildBuf = 0;
    ReceiveLen = 500;
    ReceiveBuf = 0;
    unknown_18 = -1;
    unknown_1c = 0;
    unknown_20 = 0;
    unknown_24 = 3000;
    unknown_28 = 1200;
    unknown_2c = 60;
    unknown_30 = '+';
    SendOverflows = 0;
    ReceiveOverflows = 0;
    CRCErrors = 0;
    NumConnections = 0;
    RetryDelta = 60;
    MaxRetries = -1;
    Timeout = 1200;
    ModemEntry = 0;
}
