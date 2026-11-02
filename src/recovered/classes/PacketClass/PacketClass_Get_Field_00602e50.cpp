// bool PacketClass::Get_Field(char const *id, int &data) (0x00602E50).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, int &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((int *)field->Data);
    }
    return (field) ? true : false;
}
