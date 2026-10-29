// EventClass::EventClass(int house, IPXAddressClass *address, unsigned char unknown) (0x004B6560): event type 0x29
// (ADDRESSCHANGE): the first four node bytes of the address (a UDP address's IP) and a byte.
#include "shared/event.hpp"
#include "shared/ipx_address.hpp"
// @ref ?Frame@@3HA=00a40d2c

EventClass::EventClass(int house, IPXAddressClass *address, unsigned char unknown)
{
    if (house >= 0) {
        House = house;
        Type = 0x29;
        NetNumType net;
        NetNodeType node;
        address->Get_Address(net, node);
        LongAt(0x08) = *(long *)node;
        ByteAt(0x07) = unknown;
        Frame = ::Frame;
        return;
    }
    House = 0xFF;
    Type = 0;
    Frame = ::Frame;
}
