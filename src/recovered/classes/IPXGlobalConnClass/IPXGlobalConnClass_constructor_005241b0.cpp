// IPXGlobalConnClass::IPXGlobalConnClass(int numsend, int numreceive, int maxlen, unsigned short product_id, unsigned short magicnum) (0x005241B0)
// An IPX connection with no address (two extra bytes per packet, 12 bytes
// of extra data for the sender's address) and per-receive-entry address and
// ID tables.
#include "shared/ipx_global_conn.hpp"
// @ref ??0IPXConnClass@@QAE@HHHGPAVIPXAddressClass@@HPBGH@Z=00523b70
// @ref ??_7IPXGlobalConnClass@@6B@=007a4684
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c

IPXGlobalConnClass::IPXGlobalConnClass(int numsend, int numreceive, int maxlen, unsigned short product_id, unsigned short magicnum) :
    IPXConnClass(numsend, numreceive, maxlen + 2, magicnum, 0, 0, unknown_empty_wide_839d4c, sizeof(IPXAddressClass))
{
    ProductID = product_id;
    IsBridge = 0;
    unknown_c8 = true;
    unknown_d4 = numreceive;
    unknown_d0 = new int[unknown_d4];
    unknown_cc = new IPXAddressClass[unknown_d4];
    for (int i = 0; i < unknown_d4; i++) {
        unknown_d0[i] = -1;
    }
    unknown_d8 = 0;
}
