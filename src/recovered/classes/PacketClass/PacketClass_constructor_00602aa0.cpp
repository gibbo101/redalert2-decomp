// PacketClass::PacketClass(char *curbuf) (0x00602AA0): parses a received packet (size and ID, then each field header, data and pad; Tiberian Sun packet.cpp).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

PacketClass::PacketClass(char *curbuf)
{
    Size = *(unsigned short *)curbuf;
    curbuf += sizeof(unsigned short);
    Size = ntohs(Size);
    ID = *(short *)curbuf;
    curbuf += sizeof(short);
    ID = ntohs(ID);
    Head = 0;

    int remaining_size = Size - 4;
    while (remaining_size > 0) {
        PacketField_004BAD50 *field = (PacketField_004BAD50 *)operator new(sizeof(PacketField_004BAD50));
        memcpy(field, curbuf, 8);
        curbuf += 8;
        remaining_size -= 8;

        int size = ntohs(field->Length);
        field->Data = new char[size];
        memcpy(field->Data, curbuf, size);
        curbuf += size;
        remaining_size -= size;

        int pad = (4 - (ntohs(field->Length) & 3)) & 3;
        curbuf += pad;
        remaining_size -= pad;

        field->Network_To_Host_004BB0F0();
        Add_Field(field);
    }
}
