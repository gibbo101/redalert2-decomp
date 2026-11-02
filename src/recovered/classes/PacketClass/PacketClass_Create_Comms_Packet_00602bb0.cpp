// char *PacketClass::Create_Comms_Packet(int &size) (0x00602BB0): builds the network form of the packet (Tiberian Sun packet.cpp, with the size and ID header written).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

char *PacketClass::Create_Comms_Packet(int &size)
{
    PacketField_004BAD50 *current;
    size = 4;
    for (current = Head; current; current = current->Next) {
        size += (unsigned short)8;
        size += current->Length;
        size += (4 - (size & 3)) & 3;
    }

    char *retval = new char[size];
    char *curbuf = retval;

    *(unsigned short *)curbuf = htons((unsigned short)size);
    curbuf += sizeof(unsigned short);
    *(short *)curbuf = htons(ID);
    curbuf += sizeof(short);

    for (current = Head; current; current = current->Next) {
        current->Host_To_Network_004BB080();
        memcpy(curbuf, current, 8);
        curbuf += 8;
        memcpy(curbuf, current->Data, ntohs(current->Length));
        curbuf += ntohs(current->Length);
        int pad = (4 - (ntohs(current->Length) & 3)) & 3;
        if (pad) {
            memset(curbuf, 0, pad);
            curbuf += pad;
        }
        current->Network_To_Host_004BB0F0();
    }
    return retval;
}
