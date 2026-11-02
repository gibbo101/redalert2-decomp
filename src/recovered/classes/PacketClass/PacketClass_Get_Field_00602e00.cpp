// bool PacketClass::Get_Field(char const *id, unsigned short &data) (0x00602E00).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, unsigned short &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((unsigned short *)field->Data);
    }
    return (field) ? true : false;
}
