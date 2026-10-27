// IPXConnClass::IPXConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum, IPXAddressClass *address, int id, wchar_t const *name, int extralen) (0x00523B70)
// A connection with a 2-tick retry, no retry limit and a 60-tick timeout,
// to the given address (sent directly to its node).
#include "shared/ipx_conn.hpp"
// @ref ??0ConnectionClass@@QAE@HHHGKKKH@Z=00480e20
// @ref ??_7IPXConnClass@@6B@=007a4644
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref _wcscpy=00783689
// @ref ?Get_Address@IPXAddressClass@@QAEXQAE0@Z=00523500

IPXConnClass::IPXConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum,
    IPXAddressClass *address, int id, wchar_t const *name, int extralen) :
    ConnectionClass(numsend, numreceive, maxlen, magicnum, 2, 0xFFFFFFFF, 60, extralen)
{
    NetNumType net;
    NetNodeType node;

    if (address) {
        Address = (*address);
    }
    ID = id;
    wcscpy(Name, name);
    Address.Get_Address(net, node);
    memcpy(ImmediateAddress, node, 6);
    unknown_60 = 0;
}
