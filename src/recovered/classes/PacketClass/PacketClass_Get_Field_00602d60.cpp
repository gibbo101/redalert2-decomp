// bool PacketClass::Get_Field(char const *id, unsigned char &data) (0x00602D60).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, unsigned char &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((unsigned char *)field->Data);
    }
    return (field) ? true : false;
}
