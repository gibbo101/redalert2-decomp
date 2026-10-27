// NullModemConnClass::NullModemConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum) -- 0x005CDB40
// A serial (null-modem) connection: ConnectionClass with a 60-tick retry
// delta, unlimited retries and a 1200-tick timeout; no port yet (-1) and a
// send buffer of MaxPacketLen + 11 bytes (header and checksum). Class name
// from RTTI (vtable 0x007A73C8); member names follow Westwood's
// NullModemConnClass (hypotheses). Bound by linear sweep to the ret 0x10.
#include "shared/connection.hpp"
// @ref ??0ConnectionClass@@QAE@HHHGKKKH@Z=00480e20
// @ref ??1ConnectionClass@@UAE@XZ=00480ea0
// @ref ?Init@ConnectionClass@@UAEXXZ=00480ed0
// @ref ?Send_Packet@ConnectionClass@@UAEHPAXHHE@Z=00480f00
// @ref ?Receive_Packet@ConnectionClass@@UAEHPAXH@Z=00481000
// @ref ?Get_Packet@ConnectionClass@@UAEHPAXPAH@Z=004812e0
// @ref ?Service@ConnectionClass@@UAEHXZ=00481370
// @ref ?unknown_slot6@ConnectionClass@@UAEHXZ=00481550
// @ref ?Service_Send_Queue@ConnectionClass@@UAEHXZ=004813a0
// @ref ?Service_Receive_Queue@ConnectionClass@@UAEHXZ=00481560
// @ref ??_7NullModemConnClass@@6B@=007a73c8
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b

class NullModemConnClass : public ConnectionClass {
public:
    NullModemConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum);
    virtual ~NullModemConnClass() { delete SendBuf; }                   // scalar deleting 0x005CDCD0
    void Init(int port);                                                // 0x005CDBB0
    virtual void Init();                                                // slot 1 0x005CDCC0
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id);   // slot 9 0x005CDBD0

    int PortHandle;                     // +0x4C
    char *SendBuf;                      // +0x50
};

NullModemConnClass::NullModemConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum) :
    ConnectionClass(numsend, numreceive, maxlen, magicnum, 60, (unsigned long)-1, 1200)
{
    PortHandle = -1;
    SendBuf = new char[MaxPacketLen + 11];
}
