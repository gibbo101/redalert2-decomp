// bool PacketClass::Get_Field(char const *id, char &data) (0x00602D10).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, char &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((char *)field->Data);
    }
    return (field) ? true : false;
}
