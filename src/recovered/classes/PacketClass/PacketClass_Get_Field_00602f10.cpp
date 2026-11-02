// bool PacketClass::Get_Field(char const *id, unsigned int &data) (0x00602F10).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, unsigned int &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((unsigned int *)field->Data);
    }
    return (field) ? true : false;
}
