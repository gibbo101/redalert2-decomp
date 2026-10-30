// IPXAddressClass __fastcall Unknown_0073c130(WOL::User const *user) (0x0073C130)
// The address of a user from its IP (+0x18, network order): net 0, the IP in the first four node bytes.
#include "shared/wol_sink.hpp"
#include "shared/ipx_address.hpp"
// @ref _ntohl@4=00781b72
// @ref ??0IPXAddressClass@@QAE@QAE0G@Z=00523440

IPXAddressClass __fastcall Unknown_0073c130(WOL::User const *user)
{
    NetNumType net;
    NetNodeType node;
    memset(net, 0, sizeof(net));
    memset(node, 0, sizeof(node));
    unsigned long ip = ntohl(user->unknown_18);
    node[3] = (unsigned char)ip;
    node[2] = (unsigned char)(ip >> 8);
    node[1] = (unsigned char)(ip >> 16);
    node[0] = (unsigned char)(ip >> 24);
    IPXAddressClass address(net, node, 0);
    return address;
}
