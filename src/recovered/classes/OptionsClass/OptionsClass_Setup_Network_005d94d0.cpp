// void OptionsClass::Setup_Network() (0x005D94D0)
// Sets the IPX socket (0x8813 by default, else Socket moved above 0x4000)
// and, when DestNet holds at least four dot-separated hex numbers, the
// destination network (with the broadcast node).
// @ref ??0IPXAddressClass@@QAE@QAE0G@Z=00523440
// @ref ??_C@_01PJCK@?4?$AA@=007dbe44
// @ref ??_C@_02JDLK@?$CFx?$AA@=007db4b4
// @ref ?unknown_dest_net_a3f608@@3VIPXAddressClass@@A=00a3f608
// @ref ?unknown_dest_net_set_a3f604@@3HA=00a3f604
#include "shared/options.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"

void OptionsClass::Setup_Network()
{
    if (Socket == 0xFFFF) {
        unknown_ipx_manager_a40978.Set_Socket(0x8813);
    } else if (Socket < 0x4000) {
        unknown_ipx_manager_a40978.Set_Socket(Socket + 0x4000);
    }
    int length = strlen(DestNet);
    if (length != 0) {
        char *buffer = new char[length + 1];
        strcpy(buffer, DestNet);
        NetNumType net;
        NetNodeType node;
        int index = 0;
        char *token = strtok(buffer, ".");
        while (token != 0) {
            int value;
            sscanf(token, "%x", &value);
            if (index < 4) {
                net[index] = value;
            } else {
                node[index - 4] = value;
            }
            index++;
            token = strtok(0, ".");
        }
        if (index >= 4) {
            memset(node, 0xFF, sizeof(node));
            unknown_dest_net_set_a3f604 = 1;
            unknown_dest_net_a3f608 = IPXAddressClass(net, node, 0);
        }
    }
}
