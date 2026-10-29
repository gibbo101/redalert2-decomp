// void __fastcall Unknown_00627190(UnknownGlobalPacket *packet, IPXAddressClass *address) (0x00627190).
#include "shared/queue.hpp"

void __fastcall Unknown_00627190(UnknownGlobalPacket *packet, IPXAddressClass *address)
{
    UnknownGlobalPacket *copy = new UnknownGlobalPacket;
    *copy = *packet;
    unknown_session_a3d298.GlobalPackets_8a0.Add(copy);
}
